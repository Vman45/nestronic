#include "display_assets.h"

#define nestronic_width 256
#define nestronic_height 64
static uint8_t nestronic_bits[] = {
   0x00, 0x00, 0x00, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00,
   0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0x00, 0x00, 0x00, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00,
   0x00, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0xf0, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0x0f, 0x00, 0x00, 0xfc, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 0x3f, 0x00,
   0x00, 0xfe, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xff, 0x1f, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xf8, 0xff, 0x00, 0x80, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0x01,
   0x80, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0x01, 0xc0, 0xff, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xff, 0x03, 0xe0, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x07,
   0xe0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x07, 0xf0, 0x1f, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xf8, 0x0f, 0xf0, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x0f,
   0xf8, 0x0f, 0x00, 0xfc, 0x03, 0xc0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xe0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x1f, 0xf8, 0x07, 0x00, 0xfc,
   0x07, 0xc0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x3f, 0x00, 0x00,
   0x00, 0x00, 0xe0, 0x1f, 0xfc, 0x07, 0x00, 0xfc, 0x0f, 0xc0, 0x3f, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xe0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x3f,
   0xfc, 0x03, 0x00, 0xfc, 0x0f, 0xc0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xfc, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xe0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x3f, 0xfe, 0x03, 0x00, 0xfc,
   0x1f, 0xc0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x03, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x3f, 0x00, 0x00,
   0x00, 0x00, 0xc0, 0x7f, 0xfe, 0x01, 0x00, 0xfc, 0x3f, 0xc0, 0x3f, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xe0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x80, 0x7f,
   0xfe, 0x01, 0x00, 0xfc, 0x3f, 0xc0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xfc, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x7f, 0xfe, 0x01, 0x00, 0xfc,
   0x7f, 0xc0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0x7f, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x80, 0x7f, 0xfe, 0x01, 0x00, 0xfc, 0x7b, 0xc0, 0x3f, 0x80,
   0x7f, 0x00, 0xc0, 0x3f, 0xe0, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x80, 0xff,
   0x00, 0x00, 0xc0, 0x1f, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x80, 0x7f,
   0xff, 0x00, 0x00, 0xfc, 0xfb, 0xc0, 0x3f, 0xe0, 0xff, 0x03, 0xf8, 0xff,
   0xe0, 0xff, 0x7f, 0xfe, 0xf9, 0x07, 0xe0, 0xff, 0x07, 0xfe, 0xf1, 0x7f,
   0xe0, 0x3f, 0xe0, 0xff, 0x07, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xfc,
   0xf3, 0xc1, 0x3f, 0xf8, 0xff, 0x07, 0xfc, 0xff, 0x01, 0xfc, 0x03, 0xfe,
   0xfd, 0x0f, 0xf8, 0xff, 0x0f, 0xfe, 0xfd, 0xff, 0xe0, 0x3f, 0xf0, 0xff,
   0x0f, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xfc, 0xe3, 0xc1, 0x3f, 0xf8,
   0xe1, 0x0f, 0x7e, 0xf0, 0x03, 0xfc, 0x03, 0xfe, 0xff, 0x1f, 0xfc, 0xc1,
   0x1f, 0xfe, 0xff, 0xff, 0xe0, 0x3f, 0xf8, 0xc3, 0x1f, 0x00, 0x00, 0xff,
   0xff, 0x00, 0x00, 0xfc, 0xe3, 0xc3, 0x3f, 0xfc, 0xe1, 0x1f, 0x7e, 0xe0,
   0x07, 0xfc, 0x03, 0xfe, 0x83, 0x3f, 0xfe, 0xc1, 0x3f, 0xfe, 0x07, 0xff,
   0xe1, 0x3f, 0xf8, 0xc3, 0x1f, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xfc,
   0xc3, 0xc7, 0x3f, 0xfe, 0xc0, 0x1f, 0x7f, 0xe0, 0x07, 0xfc, 0x03, 0xfe,
   0x01, 0x3f, 0xfe, 0x80, 0x3f, 0xfe, 0x01, 0xfe, 0xe1, 0x3f, 0xfc, 0x83,
   0x3f, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xfc, 0xc3, 0xc7, 0x3f, 0xfe,
   0xc0, 0x3f, 0xff, 0x00, 0x00, 0xfc, 0x03, 0xfe, 0x01, 0x3f, 0xfe, 0x80,
   0x3f, 0xfe, 0x01, 0xfe, 0xe1, 0x3f, 0xfc, 0x81, 0x3f, 0x00, 0x00, 0xff,
   0xff, 0x00, 0x00, 0xfc, 0x83, 0xcf, 0x3f, 0xff, 0xff, 0x3f, 0xfe, 0x01,
   0x00, 0xfc, 0x03, 0xfe, 0x01, 0x00, 0xff, 0x80, 0x7f, 0xfe, 0x01, 0xfe,
   0xe1, 0x3f, 0xfe, 0x81, 0x3f, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xfc,
   0x03, 0xcf, 0x3f, 0xff, 0xff, 0x3f, 0xfe, 0x1f, 0x00, 0xfc, 0x03, 0xfe,
   0x01, 0x00, 0xff, 0x80, 0x7f, 0xfe, 0x01, 0xfe, 0xe1, 0x3f, 0xfe, 0x01,
   0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xfc, 0x03, 0xdf, 0x3f, 0xff,
   0xff, 0x3f, 0xfc, 0xff, 0x00, 0xfc, 0x03, 0xfe, 0x01, 0x00, 0xff, 0x80,
   0x7f, 0xfe, 0x01, 0xfe, 0xe1, 0x3f, 0xfe, 0x01, 0x00, 0x00, 0x00, 0xff,
   0xff, 0x00, 0x00, 0xfc, 0x03, 0xfe, 0x3f, 0xff, 0x00, 0x00, 0xf0, 0xff,
   0x01, 0xfc, 0x03, 0xfe, 0x01, 0x00, 0xff, 0x80, 0x7f, 0xfe, 0x01, 0xfe,
   0xe1, 0x3f, 0xfe, 0x01, 0x00, 0x00, 0x00, 0xff, 0xfe, 0x01, 0x00, 0xfc,
   0x03, 0xfe, 0x3f, 0xff, 0x00, 0x00, 0x80, 0xff, 0x03, 0xfc, 0x03, 0xfe,
   0x01, 0x00, 0xff, 0x80, 0x7f, 0xfe, 0x01, 0xfe, 0xe1, 0x3f, 0xfe, 0x01,
   0x00, 0x00, 0x80, 0x7f, 0xfe, 0x01, 0x00, 0xfc, 0x03, 0xfc, 0x3f, 0xff,
   0x00, 0x00, 0x00, 0xf8, 0x07, 0xfc, 0x03, 0xfe, 0x01, 0x00, 0xff, 0x80,
   0x7f, 0xfe, 0x01, 0xfe, 0xe1, 0x3f, 0xfe, 0x81, 0x3f, 0x00, 0x80, 0x7f,
   0xfe, 0x01, 0x00, 0xfc, 0x03, 0xf8, 0x3f, 0xfe, 0xc0, 0x3f, 0x00, 0xf0,
   0x07, 0xfc, 0x03, 0xfe, 0x01, 0x00, 0xfe, 0x80, 0x3f, 0xfe, 0x01, 0xfe,
   0xe1, 0x3f, 0xfc, 0x81, 0x3f, 0x00, 0x80, 0x7f, 0xfe, 0x01, 0x00, 0xfc,
   0x03, 0xf8, 0x3f, 0xfe, 0xc0, 0x1f, 0x7f, 0xe0, 0x07, 0xfc, 0x03, 0xfe,
   0x01, 0x00, 0xfe, 0x80, 0x3f, 0xfe, 0x01, 0xfe, 0xe1, 0x3f, 0xfc, 0x83,
   0x1f, 0x00, 0x80, 0x7f, 0xfe, 0x03, 0x00, 0xfc, 0x03, 0xf0, 0x3f, 0xfc,
   0xc1, 0x1f, 0x7f, 0xe0, 0x07, 0xfc, 0x03, 0xfe, 0x01, 0x00, 0xfe, 0xc1,
   0x1f, 0xfe, 0x01, 0xfe, 0xe1, 0x3f, 0xf8, 0x83, 0x1f, 0x00, 0xc0, 0x7f,
   0xfc, 0x03, 0x00, 0xfc, 0x03, 0xf0, 0x3f, 0xfc, 0xc1, 0x0f, 0xfe, 0xf0,
   0x03, 0xfc, 0x03, 0xfe, 0x01, 0x00, 0xfc, 0xc1, 0x1f, 0xfe, 0x01, 0xfe,
   0xe1, 0x3f, 0xf0, 0xc7, 0x0f, 0x00, 0xc0, 0x3f, 0xfc, 0x07, 0x00, 0xfc,
   0x03, 0xe0, 0x3f, 0xf8, 0xf3, 0x0f, 0xfc, 0xff, 0x03, 0xfc, 0x03, 0xfe,
   0x01, 0x00, 0xf8, 0xff, 0x07, 0xfe, 0x01, 0xfe, 0xe1, 0x3f, 0xe0, 0xff,
   0x07, 0x00, 0xe0, 0x3f, 0xfc, 0x07, 0x00, 0xfc, 0x03, 0xc0, 0x3f, 0xf0,
   0xff, 0x03, 0xf8, 0xff, 0x01, 0xfc, 0x03, 0xfe, 0x01, 0x00, 0xe0, 0xff,
   0x03, 0xfe, 0x01, 0xfe, 0xe1, 0x3f, 0x80, 0xff, 0x03, 0x00, 0xe0, 0x3f,
   0xf8, 0x0f, 0x00, 0xfc, 0x03, 0xc0, 0x3f, 0x80, 0xff, 0x01, 0xc0, 0x3f,
   0x00, 0xfc, 0x03, 0xfe, 0x01, 0x00, 0x00, 0x7f, 0x00, 0xfe, 0x01, 0xfe,
   0xe1, 0x3f, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x1f, 0xf8, 0x0f, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xf0, 0x1f, 0xf0, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x0f,
   0xf0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x0f, 0xe0, 0x7f, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xfe, 0x07, 0xc0, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x03,
   0x80, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0x01, 0x80, 0xff, 0x07, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xe0, 0xff, 0x01, 0x00, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0x00,
   0x00, 0xfe, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0xfc, 0xff, 0x07,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xe0, 0xff, 0x3f, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00,
   0x00, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0xc0, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0x03, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
   0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 0x00 };

#define seg_a_width 36
#define seg_a_height 8
static uint8_t seg_a_bits[] = {
   0xfe, 0xff, 0xff, 0xff, 0x07, 0xfc, 0xff, 0xff, 0xff, 0x03, 0xf8, 0xff,
   0xff, 0xff, 0x01, 0xf0, 0xff, 0xff, 0xff, 0x00, 0xe0, 0xff, 0xff, 0x7f,
   0x00, 0xc0, 0xff, 0xff, 0x3f, 0x00, 0x80, 0xff, 0xff, 0x1f, 0x00, 0x00,
   0xff, 0xff, 0x0f, 0x00 };
#define seg_b_width 8
#define seg_b_height 32
static uint8_t seg_b_bits[] = {
   0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0x7e, 0x3c, 0x18, 0x00 };
#define seg_c_width 8
#define seg_c_height 32
static uint8_t seg_c_bits[] = {
   0x00, 0x18, 0x3c, 0x7e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0x00 };
#define seg_d_width 36
#define seg_d_height 8
static uint8_t seg_d_bits[] = {
   0x00, 0xff, 0xff, 0x0f, 0x00, 0x80, 0xff, 0xff, 0x1f, 0x00, 0xc0, 0xff,
   0xff, 0x3f, 0x00, 0xe0, 0xff, 0xff, 0x7f, 0x00, 0xf0, 0xff, 0xff, 0xff,
   0x00, 0xf8, 0xff, 0xff, 0xff, 0x01, 0xfc, 0xff, 0xff, 0xff, 0x03, 0xfe,
   0xff, 0xff, 0xff, 0x07 };
#define seg_e_width 8
#define seg_e_height 32
static uint8_t seg_e_bits[] = {
   0x00, 0x18, 0x3c, 0x7e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00 };
#define seg_f_width 8
#define seg_f_height 32
static uint8_t seg_f_bits[] = {
   0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0x7e, 0x3c, 0x18, 0x00 };
#define seg_g_width 36
#define seg_g_height 8
static uint8_t seg_g_bits[] = {
   0x00, 0xff, 0xff, 0x0f, 0x00, 0x80, 0xff, 0xff, 0x1f, 0x00, 0xc0, 0xff,
   0xff, 0x3f, 0x00, 0xe0, 0xff, 0xff, 0x7f, 0x00, 0xe0, 0xff, 0xff, 0x7f,
   0x00, 0xc0, 0xff, 0xff, 0x3f, 0x00, 0x80, 0xff, 0xff, 0x1f, 0x00, 0x00,
   0xff, 0xff, 0x0f, 0x00 };

#define seg_sep_width 8
#define seg_sep_height 30
static uint8_t seg_sep_bits[] = {
   0x3c, 0x7e, 0xff, 0xff, 0xff, 0xff, 0x7e, 0x3c, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x7e,
   0xff, 0xff, 0xff, 0xff, 0x7e, 0x3c };

#define tseg_ch_a_width 14
#define tseg_ch_a_height 24
static uint8_t tseg_ch_a_bits[] = {
   0xfe, 0x1f, 0xfd, 0x2f, 0xfb, 0x37, 0x07, 0x38, 0x07, 0x38, 0x07, 0x38,
   0x07, 0x38, 0x07, 0x38, 0x07, 0x38, 0x07, 0x38, 0x07, 0x38, 0xfa, 0x17,
   0xfc, 0x0f, 0xfa, 0x17, 0x07, 0x38, 0x07, 0x38, 0x07, 0x38, 0x07, 0x38,
   0x07, 0x38, 0x07, 0x38, 0x07, 0x38, 0x07, 0x38, 0x03, 0x30, 0x01, 0x20 };

#define tseg_ch_p_width 14
#define tseg_ch_p_height 24
static uint8_t tseg_ch_p_bits[] = {
   0xfe, 0x1f, 0xfd, 0x2f, 0xfb, 0x37, 0x07, 0x38, 0x07, 0x38, 0x07, 0x38,
   0x07, 0x38, 0x07, 0x38, 0x07, 0x38, 0x07, 0x38, 0x07, 0x38, 0xfa, 0x17,
   0xfc, 0x0f, 0xfa, 0x07, 0x07, 0x00, 0x07, 0x00, 0x07, 0x00, 0x07, 0x00,
   0x07, 0x00, 0x07, 0x00, 0x07, 0x00, 0x07, 0x00, 0x03, 0x00, 0x01, 0x00 };

#define tseg_ch_m_width 14
#define tseg_ch_m_height 24
static uint8_t tseg_ch_m_bits[] = {
   0x07, 0x38, 0x07, 0x38, 0x0f, 0x3c, 0x0f, 0x3c, 0x1f, 0x3e, 0x1f, 0x3e,
   0x37, 0x3b, 0x37, 0x3b, 0xe7, 0x39, 0xe7, 0x39, 0xc7, 0x38, 0xc2, 0x10,
   0x00, 0x00, 0x02, 0x10, 0x07, 0x38, 0x07, 0x38, 0x07, 0x38, 0x07, 0x38,
   0x07, 0x38, 0x07, 0x38, 0x07, 0x38, 0x07, 0x38, 0x03, 0x30, 0x01, 0x20 };

#define clock_icon_width 22
#define clock_icon_height 32
static unsigned char clock_icon_bits[] = {
   0xc0, 0xff, 0x00, 0xc0, 0xff, 0x00, 0xc0, 0xff, 0x00, 0xc0, 0xff, 0x00,
   0x00, 0x0c, 0x00, 0x00, 0x0c, 0x00, 0xc0, 0xff, 0x00, 0xc0, 0xff, 0x00,
   0xf0, 0xcc, 0x03, 0xf0, 0xcc, 0x03, 0x3c, 0x00, 0x0f, 0x3c, 0x00, 0x0f,
   0x0c, 0x00, 0x0c, 0x0c, 0x00, 0x0c, 0xcf, 0xc0, 0x3c, 0xcf, 0xc0, 0x3c,
   0x03, 0x33, 0x30, 0x03, 0x33, 0x30, 0x0f, 0x0c, 0x3c, 0x0f, 0x0c, 0x3c,
   0x03, 0x00, 0x30, 0x03, 0x00, 0x30, 0x0f, 0x00, 0x3c, 0x0f, 0x00, 0x3c,
   0x0c, 0x00, 0x0c, 0x0c, 0x00, 0x0c, 0x3c, 0x00, 0x0f, 0x3c, 0x00, 0x0f,
   0xf0, 0xcc, 0x03, 0xf0, 0xcc, 0x03, 0xc0, 0xff, 0x00, 0xc0, 0xff, 0x00 };

#define snooze_icon_width 22
#define snooze_icon_height 32
static unsigned char snooze_icon_bits[] = {
   0xc0, 0xff, 0x00, 0xc0, 0xff, 0x00, 0xc0, 0xff, 0x00, 0xc0, 0xff, 0x00,
   0x00, 0x0c, 0x00, 0x00, 0x0c, 0x00, 0xc0, 0xff, 0x00, 0xc0, 0xff, 0x00,
   0xf0, 0xcc, 0x03, 0xf0, 0xcc, 0x03, 0x3c, 0x00, 0x0f, 0x3c, 0x00, 0x0f,
   0x0c, 0x00, 0x0c, 0xec, 0xff, 0x0d, 0xef, 0xff, 0x3d, 0x0f, 0xf0, 0x3d,
   0x03, 0xfc, 0x30, 0x03, 0xfc, 0x30, 0x0f, 0x3f, 0x3c, 0x0f, 0x3f, 0x3c,
   0xc3, 0x0f, 0x30, 0xc3, 0x0f, 0x30, 0xef, 0x03, 0x3c, 0xef, 0xff, 0x3d,
   0xec, 0xff, 0x0d, 0x0c, 0x00, 0x0c, 0x3c, 0x00, 0x0f, 0x3c, 0x00, 0x0f,
   0xf0, 0xcc, 0x03, 0xf0, 0xcc, 0x03, 0xc0, 0xff, 0x00, 0xc0, 0xff, 0x00 };

uint8_t display_asset_get(asset_info_t *asset_info, asset_name_t asset_name)
{
    switch (asset_name) {
    case ASSET_NESTRONIC:
        *asset_info = (asset_info_t) {
            .bits = nestronic_bits,
            .height = nestronic_height,
            .width = nestronic_width
        };
        return 1;
    case ASSET_SEG_A:
        *asset_info = (asset_info_t) {
            .bits = seg_a_bits,
            .height = seg_a_height,
            .width = seg_a_width
        };
        return 1;
    case ASSET_SEG_B:
        *asset_info = (asset_info_t) {
            .bits = seg_b_bits,
            .height = seg_b_height,
            .width = seg_b_width
        };
        return 1;
    case ASSET_SEG_C:
        *asset_info = (asset_info_t) {
            .bits = seg_c_bits,
            .height = seg_c_height,
            .width = seg_c_width
        };
        return 1;
    case ASSET_SEG_D:
        *asset_info = (asset_info_t) {
            .bits = seg_d_bits,
            .height = seg_d_height,
            .width = seg_d_width
        };
        return 1;
    case ASSET_SEG_E:
        *asset_info = (asset_info_t) {
            .bits = seg_e_bits,
            .height = seg_e_height,
            .width = seg_e_width
        };
        return 1;
    case ASSET_SEG_F:
        *asset_info = (asset_info_t) {
            .bits = seg_f_bits,
            .height = seg_f_height,
            .width = seg_f_width
        };
        return 1;
    case ASSET_SEG_G:
        *asset_info = (asset_info_t) {
            .bits = seg_g_bits,
            .height = seg_g_height,
            .width = seg_g_width
        };
        return 1;
    case ASSET_SEG_SEP:
        *asset_info = (asset_info_t) {
            .bits = seg_sep_bits,
            .height = seg_sep_height,
            .width = seg_sep_width
        };
        return 1;
    case ASSET_TSEG_CH_A:
        *asset_info = (asset_info_t) {
            .bits = tseg_ch_a_bits,
            .height = tseg_ch_a_height,
            .width = tseg_ch_a_width
        };
        return 1;
    case ASSET_TSEG_CH_P:
        *asset_info = (asset_info_t) {
            .bits = tseg_ch_p_bits,
            .height = tseg_ch_p_height,
            .width = tseg_ch_p_width
        };
        return 1;
    case ASSET_TSEG_CH_M:
        *asset_info = (asset_info_t) {
            .bits = tseg_ch_m_bits,
            .height = tseg_ch_m_height,
            .width = tseg_ch_m_width
        };
        return 1;
    case ASSET_CLOCK_ICON:
        *asset_info = (asset_info_t) {
            .bits = clock_icon_bits,
            .height = clock_icon_height,
            .width = clock_icon_width
        };
        return 1;
    case ASSET_SNOOZE_ICON:
        *asset_info = (asset_info_t) {
            .bits = snooze_icon_bits,
            .height = snooze_icon_height,
            .width = snooze_icon_width
        };
        return 1;
    default:
        return 0;
    }
}
