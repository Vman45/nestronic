#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/event_groups.h>
#include <esp_system.h>
#include <esp_event.h>
#include <esp_event_loop.h>
#include <esp_err.h>
#include <esp_log.h>
#include <esp_vfs_fat.h>
#include <nvs_flash.h>
#include <driver/gpio.h>
#include <driver/sdspi_host.h>
#include <driver/i2c.h>
#include <driver/adc.h>
#include <esp_adc_cal.h>
#include <esp_intr_alloc.h>
#include <lwip/err.h>
#include <apps/sntp/sntp.h>

#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>

#include "board_config.h"
#include "settings.h"
#include "time_handler.h"
#include "wifi_handler.h"
#include "i2c_util.h"
#include "sdcard_util.h"
#include "display.h"
#include "board_rtc.h"
#include "keypad.h"
#include "mcp40d17.h"
#include "vgm_player.h"
#include "main_menu.h"

static const char *TAG = "main";

// ADC voltage reference
//#define V_REF_TO_GPIO
#define V_REF 1116 // 1.1175V

static xQueueHandle gpio_event_queue = NULL;

static void gpio_poll_task(void *pvParameters)
{
    int last_rheo_val = -1;
    int last_cd_level = -1;
    int last_cd_count = 0;

    while (1) {
        // Check the volume control and adjust the amplifier volume
        int val = adc1_get_raw(ADC1_VOL_PIN);
        int rheo_val = val >> 5;
        if (last_rheo_val < 0 || abs(rheo_val - last_rheo_val) > 1) {
            i2c_mutex_lock(I2C_P0_NUM);
            mcp40d17_set_wiper(I2C_P0_NUM, 0x7F & rheo_val);
            i2c_mutex_unlock(I2C_P0_NUM);
            ESP_LOGI(TAG, "Set volume: %d", rheo_val);
            last_rheo_val = rheo_val;
        }

        // Check the SD card detect pin
        int level = gpio_get_level(SDMMC_CD);
        if (last_cd_level < 0 || last_cd_level != level) {
            last_cd_level = level;
            last_cd_count = 0;
        } else if (last_cd_count < 3) {
            last_cd_count++;
        }
        if (last_cd_count == 3) {
            last_cd_count++;
            if (last_cd_level == 0) {
                ESP_LOGI(TAG, "SD/MMC Card Inserted");
                if (sdcard_mount("/sdcard") != ESP_OK) {
                    display_message("Error", "Could not read SD card", NULL, " OK ");
                }
            } else if (sdcard_is_mounted()) {
                ESP_LOGI(TAG, "SD/MMC Card Ejected");
                sdcard_unmount();
            }
        }

        vTaskDelay(100 / portTICK_RATE_MS);
    }
}

static void gpio_queue_task(void *arg)
{
    uint32_t io_num;
    for(;;) {
        if(xQueueReceive(gpio_event_queue, &io_num, portMAX_DELAY)) {
            if (io_num == MCP7940_MFP_PIN) {
                board_rtc_int_event_handler();
            }
            else if (io_num == TCA8418_INT_PIN) {
                keypad_int_event_handler();
            }
            else {
                ESP_LOGI(TAG, "GPIO[%d] intr, val: %d", io_num, gpio_get_level(io_num));
            }
        }
    }
}

static void IRAM_ATTR gpio_isr_handler(void *arg)
{
    uint32_t gpio_num = (uint32_t) arg;
    xQueueSendFromISR(gpio_event_queue, &gpio_num, NULL);
}

static void adc_input_init(void)
{
    ESP_ERROR_CHECK(adc1_config_width(ADC_WIDTH_BIT_12));
    ESP_ERROR_CHECK(adc1_config_channel_atten(ADC1_VOL_PIN, ADC_ATTEN_DB_11));
    ESP_ERROR_CHECK(adc1_config_channel_atten(ADC1_LUM_PIN, ADC_ATTEN_DB_2_5));
}

static void gpio_isr_init(void)
{
    gpio_event_queue = xQueueCreate(10, sizeof(uint32_t));
    xTaskCreate(gpio_queue_task, "gpio_queue_task", 2048, NULL, 10, NULL);
    ESP_ERROR_CHECK(gpio_install_isr_service(0 /*ESP_INTR_FLAG_DEFAULT*/));
}

static void rtc_init_helper(void)
{
    ESP_ERROR_CHECK(board_rtc_init());
    gpio_isr_handler_add(MCP7940_MFP_PIN, gpio_isr_handler, (void*)MCP7940_MFP_PIN);
}

static void keypad_init_helper(void)
{
    if (keypad_init() == ESP_OK) {
        gpio_isr_handler_add(TCA8418_INT_PIN, gpio_isr_handler, (void*)TCA8418_INT_PIN);
    } else {
        ESP_LOGE(TAG, "Unable to initialize keypad");
    }
}

void app_main(void)
{
    esp_err_t ret;

    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_LOGI(TAG, "Nestronic System Firmware");
    ESP_LOGI(TAG, "-------------------------");

#ifdef V_REF_TO_GPIO
    // ADC calibration
    ret = adc2_vref_to_gpio(ADC2_VREF_PIN);
    if (ret == ESP_OK){
        ESP_LOGI(TAG, "V_REF routed to GPIO27");
    } else {
        ESP_LOGE(TAG, "Failed to route V_REF");
    }
    vTaskDelay(60000 / portTICK_RATE_MS);
#endif

    // Initialize I2C port 0 (on-board devices)
    ESP_ERROR_CHECK(i2c_init_master_port0());

    // Initialize I2C port 1 (input board devices)
    ESP_ERROR_CHECK(i2c_init_master_port1());

    // Initialize the display, don't fail on errors
    ret = display_init();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Unable to initialize display");
    }

    // Show the startup logo
    display_draw_logo();

    // Initialize the ADC inputs
    adc_input_init();

    // Initialize the SD card interface
    ESP_ERROR_CHECK(sdcard_init());

    // Initialize the GPIO ISR and event queue, needed for
    // RTC and keypad event handling.
    gpio_isr_init();

    // Initialize the external RTC chip
    rtc_init_helper();

    // Initialize the system time
    ESP_ERROR_CHECK(time_handler_init());

    // Initialize the WiFi interface
    tcpip_adapter_init();
    ESP_ERROR_CHECK(wifi_handler_init());

    // Initialize the keypad controller, don't fail on errors
    keypad_init_helper();

    // Start the task that polls certain input pins
    xTaskCreate(gpio_poll_task, "gpio_poll_task", 4096, NULL, 5, NULL);

    // Initialize the VGM player task
    ESP_ERROR_CHECK(vgm_player_init());

    // Show the menu system
    vTaskDelay(1000 / portTICK_RATE_MS);
    main_menu_start();
}