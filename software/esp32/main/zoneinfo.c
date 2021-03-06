#include "zoneinfo.h"

#include <string.h>

#include "vpool.h"

static const char* const zoneinfo_data[] = {
        "Africa/Abidjan", "GMT0",
        "Africa/Accra", "GMT0",
        "Africa/Addis_Ababa", "EAT-3",
        "Africa/Algiers", "CET-1",
        "Africa/Asmara", "EAT-3",
        "Africa/Asmera", "EAT-3",
        "Africa/Bamako", "GMT0",
        "Africa/Bangui", "WAT-1",
        "Africa/Banjul", "GMT0",
        "Africa/Bissau", "GMT0",
        "Africa/Blantyre", "CAT-2",
        "Africa/Brazzaville", "WAT-1",
        "Africa/Bujumbura", "CAT-2",
        "Africa/Cairo", "EET-2",
        "Africa/Casablanca", "WET0WEST,M3.5.0,M10.5.0/3",
        "Africa/Ceuta", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Africa/Conakry", "GMT0",
        "Africa/Dakar", "GMT0",
        "Africa/Dar_es_Salaam", "EAT-3",
        "Africa/Djibouti", "EAT-3",
        "Africa/Douala", "WAT-1",
        "Africa/El_Aaiun", "WET0WEST,M3.5.0,M10.5.0/3",
        "Africa/Freetown", "GMT0",
        "Africa/Gaborone", "CAT-2",
        "Africa/Harare", "CAT-2",
        "Africa/Johannesburg", "SAST-2",
        "Africa/Juba", "EAT-3",
        "Africa/Kampala", "EAT-3",
        "Africa/Khartoum", "CAT-2",
        "Africa/Kigali", "CAT-2",
        "Africa/Kinshasa", "WAT-1",
        "Africa/Lagos", "WAT-1",
        "Africa/Libreville", "WAT-1",
        "Africa/Lome", "GMT0",
        "Africa/Luanda", "WAT-1",
        "Africa/Lubumbashi", "CAT-2",
        "Africa/Lusaka", "CAT-2",
        "Africa/Malabo", "WAT-1",
        "Africa/Maputo", "CAT-2",
        "Africa/Maseru", "SAST-2",
        "Africa/Mbabane", "SAST-2",
        "Africa/Mogadishu", "EAT-3",
        "Africa/Monrovia", "GMT0",
        "Africa/Nairobi", "EAT-3",
        "Africa/Ndjamena", "WAT-1",
        "Africa/Niamey", "WAT-1",
        "Africa/Nouakchott", "GMT0",
        "Africa/Ouagadougou", "GMT0",
        "Africa/Porto-Novo", "WAT-1",
        "Africa/Sao_Tome", "WAT-1",
        "Africa/Timbuktu", "GMT0",
        "Africa/Tripoli", "EET-2",
        "Africa/Tunis", "CET-1",
        "Africa/Windhoek", "CAT-2",
        "America/Adak", "HST10HDT,M3.2.0,M11.1.0",
        "America/Anchorage", "AKST9AKDT,M3.2.0,M11.1.0",
        "America/Anguilla", "AST4",
        "America/Antigua", "AST4",
        "America/Aruba", "AST4",
        "America/Atikokan", "EST5",
        "America/Atka", "HST10HDT,M3.2.0,M11.1.0",
        "America/Bahia_Banderas", "CST6CDT,M4.1.0,M10.5.0",
        "America/Barbados", "AST4",
        "America/Belize", "CST6",
        "America/Blanc-Sablon", "AST4",
        "America/Boise", "MST7MDT,M3.2.0,M11.1.0",
        "America/Cambridge_Bay", "MST7MDT,M3.2.0,M11.1.0",
        "America/Cancun", "EST5",
        "America/Cayman", "EST5",
        "America/Chicago", "CST6CDT,M3.2.0,M11.1.0",
        "America/Chihuahua", "MST7MDT,M4.1.0,M10.5.0",
        "America/Coral_Harbour", "EST5",
        "America/Costa_Rica", "CST6",
        "America/Creston", "MST7",
        "America/Curacao", "AST4",
        "America/Danmarkshavn", "GMT0",
        "America/Dawson_Creek", "MST7",
        "America/Dawson", "PST8PDT,M3.2.0,M11.1.0",
        "America/Denver", "MST7MDT,M3.2.0,M11.1.0",
        "America/Detroit", "EST5EDT,M3.2.0,M11.1.0",
        "America/Dominica", "AST4",
        "America/Edmonton", "MST7MDT,M3.2.0,M11.1.0",
        "America/El_Salvador", "CST6",
        "America/Ensenada", "PST8PDT,M3.2.0,M11.1.0",
        "America/Fort_Nelson", "MST7",
        "America/Fort_Wayne", "EST5EDT,M3.2.0,M11.1.0",
        "America/Glace_Bay", "AST4ADT,M3.2.0,M11.1.0",
        "America/Goose_Bay", "AST4ADT,M3.2.0,M11.1.0",
        "America/Grand_Turk", "EST5EDT,M3.2.0,M11.1.0",
        "America/Grenada", "AST4",
        "America/Guadeloupe", "AST4",
        "America/Guatemala", "CST6",
        "America/Halifax", "AST4ADT,M3.2.0,M11.1.0",
        "America/Havana", "CST5CDT,M3.2.0/0,M11.1.0/1",
        "America/Hermosillo", "MST7",
        "America/Indiana/Indianapolis", "EST5EDT,M3.2.0,M11.1.0",
        "America/Indiana/Knox", "CST6CDT,M3.2.0,M11.1.0",
        "America/Indiana/Marengo", "EST5EDT,M3.2.0,M11.1.0",
        "America/Indiana/Petersburg", "EST5EDT,M3.2.0,M11.1.0",
        "America/Indianapolis", "EST5EDT,M3.2.0,M11.1.0",
        "America/Indiana/Tell_City", "CST6CDT,M3.2.0,M11.1.0",
        "America/Indiana/Vevay", "EST5EDT,M3.2.0,M11.1.0",
        "America/Indiana/Vincennes", "EST5EDT,M3.2.0,M11.1.0",
        "America/Indiana/Winamac", "EST5EDT,M3.2.0,M11.1.0",
        "America/Inuvik", "MST7MDT,M3.2.0,M11.1.0",
        "America/Iqaluit", "EST5EDT,M3.2.0,M11.1.0",
        "America/Jamaica", "EST5",
        "America/Juneau", "AKST9AKDT,M3.2.0,M11.1.0",
        "America/Kentucky/Louisville", "EST5EDT,M3.2.0,M11.1.0",
        "America/Kentucky/Monticello", "EST5EDT,M3.2.0,M11.1.0",
        "America/Knox_IN", "CST6CDT,M3.2.0,M11.1.0",
        "America/Kralendijk", "AST4",
        "America/Los_Angeles", "PST8PDT,M3.2.0,M11.1.0",
        "America/Louisville", "EST5EDT,M3.2.0,M11.1.0",
        "America/Lower_Princes", "AST4",
        "America/Managua", "CST6",
        "America/Marigot", "AST4",
        "America/Martinique", "AST4",
        "America/Matamoros", "CST6CDT,M3.2.0,M11.1.0",
        "America/Mazatlan", "MST7MDT,M4.1.0,M10.5.0",
        "America/Menominee", "CST6CDT,M3.2.0,M11.1.0",
        "America/Merida", "CST6CDT,M4.1.0,M10.5.0",
        "America/Metlakatla", "AKST9AKDT,M3.2.0,M11.1.0",
        "America/Mexico_City", "CST6CDT,M4.1.0,M10.5.0",
        "America/Moncton", "AST4ADT,M3.2.0,M11.1.0",
        "America/Monterrey", "CST6CDT,M4.1.0,M10.5.0",
        "America/Montreal", "EST5EDT,M3.2.0,M11.1.0",
        "America/Montserrat", "AST4",
        "America/Nassau", "EST5EDT,M3.2.0,M11.1.0",
        "America/New_York", "EST5EDT,M3.2.0,M11.1.0",
        "America/Nipigon", "EST5EDT,M3.2.0,M11.1.0",
        "America/Nome", "AKST9AKDT,M3.2.0,M11.1.0",
        "America/North_Dakota/Beulah", "CST6CDT,M3.2.0,M11.1.0",
        "America/North_Dakota/Center", "CST6CDT,M3.2.0,M11.1.0",
        "America/North_Dakota/New_Salem", "CST6CDT,M3.2.0,M11.1.0",
        "America/Ojinaga", "MST7MDT,M3.2.0,M11.1.0",
        "America/Panama", "EST5",
        "America/Pangnirtung", "EST5EDT,M3.2.0,M11.1.0",
        "America/Phoenix", "MST7",
        "America/Port-au-Prince", "EST5EDT,M3.2.0,M11.1.0",
        "America/Port_of_Spain", "AST4",
        "America/Puerto_Rico", "AST4",
        "America/Rainy_River", "CST6CDT,M3.2.0,M11.1.0",
        "America/Rankin_Inlet", "CST6CDT,M3.2.0,M11.1.0",
        "America/Regina", "CST6",
        "America/Resolute", "CST6CDT,M3.2.0,M11.1.0",
        "America/Santa_Isabel", "PST8PDT,M3.2.0,M11.1.0",
        "America/Santo_Domingo", "AST4",
        "America/Shiprock", "MST7MDT,M3.2.0,M11.1.0",
        "America/Sitka", "AKST9AKDT,M3.2.0,M11.1.0",
        "America/St_Barthelemy", "AST4",
        "America/St_Johns", "NST3:30NDT,M3.2.0,M11.1.0",
        "America/St_Kitts", "AST4",
        "America/St_Lucia", "AST4",
        "America/St_Thomas", "AST4",
        "America/St_Vincent", "AST4",
        "America/Swift_Current", "CST6",
        "America/Tegucigalpa", "CST6",
        "America/Thule", "AST4ADT,M3.2.0,M11.1.0",
        "America/Thunder_Bay", "EST5EDT,M3.2.0,M11.1.0",
        "America/Tijuana", "PST8PDT,M3.2.0,M11.1.0",
        "America/Toronto", "EST5EDT,M3.2.0,M11.1.0",
        "America/Tortola", "AST4",
        "America/Vancouver", "PST8PDT,M3.2.0,M11.1.0",
        "America/Virgin", "AST4",
        "America/Whitehorse", "PST8PDT,M3.2.0,M11.1.0",
        "America/Winnipeg", "CST6CDT,M3.2.0,M11.1.0",
        "America/Yakutat", "AKST9AKDT,M3.2.0,M11.1.0",
        "America/Yellowknife", "MST7MDT,M3.2.0,M11.1.0",
        "Antarctica/McMurdo", "NZST-12NZDT,M9.5.0,M4.1.0/3",
        "Antarctica/South_Pole", "NZST-12NZDT,M9.5.0,M4.1.0/3",
        "Arctic/Longyearbyen", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Asia/Amman", "EET-2EEST,M3.5.4/24,M10.5.5/1",
        "Asia/Beirut", "EET-2EEST,M3.5.0/0,M10.5.0/0",
        "Asia/Calcutta", "IST-5:30",
        "Asia/Chongqing", "CST-8",
        "Asia/Chungking", "CST-8",
        "Asia/Damascus", "EET-2EEST,M3.5.5/0,M10.5.5/0",
        "Asia/Famagusta", "EET-2EEST,M3.5.0/3,M10.5.0/4",
        "Asia/Gaza", "EET-2EEST,M3.4.6/1,M10.5.6/1",
        "Asia/Harbin", "CST-8",
        "Asia/Hebron", "EET-2EEST,M3.4.6/1,M10.5.6/1",
        "Asia/Hong_Kong", "HKT-8",
        "Asia/Jakarta", "WIB-7",
        "Asia/Jayapura", "WIT-9",
        "Asia/Jerusalem", "IST-2IDT,M3.4.4/26,M10.5.0",
        "Asia/Karachi", "PKT-5",
        "Asia/Kolkata", "IST-5:30",
        "Asia/Macao", "CST-8",
        "Asia/Macau", "CST-8",
        "Asia/Makassar", "WITA-8",
        "Asia/Nicosia", "EET-2EEST,M3.5.0/3,M10.5.0/4",
        "Asia/Pontianak", "WIB-7",
        "Asia/Pyongyang", "KST-8:30",
        "Asia/Seoul", "KST-9",
        "Asia/Shanghai", "CST-8",
        "Asia/Taipei", "CST-8",
        "Asia/Tel_Aviv", "IST-2IDT,M3.4.4/26,M10.5.0",
        "Asia/Tokyo", "JST-9",
        "Asia/Ujung_Pandang", "WITA-8",
        "Atlantic/Bermuda", "AST4ADT,M3.2.0,M11.1.0",
        "Atlantic/Canary", "WET0WEST,M3.5.0/1,M10.5.0",
        "Atlantic/Faeroe", "WET0WEST,M3.5.0/1,M10.5.0",
        "Atlantic/Faroe", "WET0WEST,M3.5.0/1,M10.5.0",
        "Atlantic/Jan_Mayen", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Atlantic/Madeira", "WET0WEST,M3.5.0/1,M10.5.0",
        "Atlantic/Reykjavik", "GMT0",
        "Atlantic/St_Helena", "GMT0",
        "Australia/ACT", "AEST-10AEDT,M10.1.0,M4.1.0/3",
        "Australia/Adelaide", "ACST-9:30ACDT,M10.1.0,M4.1.0/3",
        "Australia/Brisbane", "AEST-10",
        "Australia/Broken_Hill", "ACST-9:30ACDT,M10.1.0,M4.1.0/3",
        "Australia/Canberra", "AEST-10AEDT,M10.1.0,M4.1.0/3",
        "Australia/Currie", "AEST-10AEDT,M10.1.0,M4.1.0/3",
        "Australia/Darwin", "ACST-9:30",
        "Australia/Hobart", "AEST-10AEDT,M10.1.0,M4.1.0/3",
        "Australia/Lindeman", "AEST-10",
        "Australia/Melbourne", "AEST-10AEDT,M10.1.0,M4.1.0/3",
        "Australia/North", "ACST-9:30",
        "Australia/NSW", "AEST-10AEDT,M10.1.0,M4.1.0/3",
        "Australia/Perth", "AWST-8",
        "Australia/Queensland", "AEST-10",
        "Australia/South", "ACST-9:30ACDT,M10.1.0,M4.1.0/3",
        "Australia/Sydney", "AEST-10AEDT,M10.1.0,M4.1.0/3",
        "Australia/Tasmania", "AEST-10AEDT,M10.1.0,M4.1.0/3",
        "Australia/Victoria", "AEST-10AEDT,M10.1.0,M4.1.0/3",
        "Australia/West", "AWST-8",
        "Australia/Yancowinna", "ACST-9:30ACDT,M10.1.0,M4.1.0/3",
        "Canada/Atlantic", "AST4ADT,M3.2.0,M11.1.0",
        "Canada/Central", "CST6CDT,M3.2.0,M11.1.0",
        "Canada/Eastern", "EST5EDT,M3.2.0,M11.1.0",
        "Canada/Mountain", "MST7MDT,M3.2.0,M11.1.0",
        "Canada/Newfoundland", "NST3:30NDT,M3.2.0,M11.1.0",
        "Canada/Pacific", "PST8PDT,M3.2.0,M11.1.0",
        "Canada/Saskatchewan", "CST6",
        "Canada/Yukon", "PST8PDT,M3.2.0,M11.1.0",
        "Etc/GMT-0", "GMT0",
        "Etc/GMT+0", "GMT0",
        "Etc/GMT0", "GMT0",
        "Etc/GMT", "GMT0",
        "Etc/Greenwich", "GMT0",
        "Etc/UCT", "UCT0",
        "Etc/Universal", "UTC0",
        "Etc/UTC", "UTC0",
        "Etc/Zulu", "UTC0",
        "Europe/Amsterdam", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Europe/Andorra", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Europe/Athens", "EET-2EEST,M3.5.0/3,M10.5.0/4",
        "Europe/Belfast", "GMT0BST,M3.5.0/1,M10.5.0",
        "Europe/Belgrade", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Europe/Berlin", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Europe/Bratislava", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Europe/Brussels", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Europe/Bucharest", "EET-2EEST,M3.5.0/3,M10.5.0/4",
        "Europe/Budapest", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Europe/Busingen", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Europe/Chisinau", "EET-2EEST,M3.5.0,M10.5.0/3",
        "Europe/Copenhagen", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Europe/Dublin", "GMT0IST,M3.5.0/1,M10.5.0",
        "Europe/Gibraltar", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Europe/Guernsey", "GMT0BST,M3.5.0/1,M10.5.0",
        "Europe/Helsinki", "EET-2EEST,M3.5.0/3,M10.5.0/4",
        "Europe/Isle_of_Man", "GMT0BST,M3.5.0/1,M10.5.0",
        "Europe/Jersey", "GMT0BST,M3.5.0/1,M10.5.0",
        "Europe/Kaliningrad", "EET-2",
        "Europe/Kiev", "EET-2EEST,M3.5.0/3,M10.5.0/4",
        "Europe/Lisbon", "WET0WEST,M3.5.0/1,M10.5.0",
        "Europe/Ljubljana", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Europe/London", "GMT0BST,M3.5.0/1,M10.5.0",
        "Europe/Luxembourg", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Europe/Madrid", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Europe/Malta", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Europe/Mariehamn", "EET-2EEST,M3.5.0/3,M10.5.0/4",
        "Europe/Monaco", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Europe/Moscow", "MSK-3",
        "Europe/Nicosia", "EET-2EEST,M3.5.0/3,M10.5.0/4",
        "Europe/Oslo", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Europe/Paris", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Europe/Podgorica", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Europe/Prague", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Europe/Riga", "EET-2EEST,M3.5.0/3,M10.5.0/4",
        "Europe/Rome", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Europe/San_Marino", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Europe/Sarajevo", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Europe/Simferopol", "MSK-3",
        "Europe/Skopje", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Europe/Sofia", "EET-2EEST,M3.5.0/3,M10.5.0/4",
        "Europe/Stockholm", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Europe/Tallinn", "EET-2EEST,M3.5.0/3,M10.5.0/4",
        "Europe/Tirane", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Europe/Tiraspol", "EET-2EEST,M3.5.0,M10.5.0/3",
        "Europe/Uzhgorod", "EET-2EEST,M3.5.0/3,M10.5.0/4",
        "Europe/Vaduz", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Europe/Vatican", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Europe/Vienna", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Europe/Vilnius", "EET-2EEST,M3.5.0/3,M10.5.0/4",
        "Europe/Warsaw", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Europe/Zagreb", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Europe/Zaporozhye", "EET-2EEST,M3.5.0/3,M10.5.0/4",
        "Europe/Zurich", "CET-1CEST,M3.5.0,M10.5.0/3",
        "Indian/Antananarivo", "EAT-3",
        "Indian/Comoro", "EAT-3",
        "Indian/Mayotte", "EAT-3",
        "Mexico/BajaNorte", "PST8PDT,M3.2.0,M11.1.0",
        "Mexico/BajaSur", "MST7MDT,M4.1.0,M10.5.0",
        "Mexico/General", "CST6CDT,M4.1.0,M10.5.0",
        "Pacific/Auckland", "NZST-12NZDT,M9.5.0,M4.1.0/3",
        "Pacific/Guam", "ChST-10",
        "Pacific/Honolulu", "HST10",
        "Pacific/Johnston", "HST10",
        "Pacific/Midway", "SST11",
        "Pacific/Pago_Pago", "SST11",
        "Pacific/Saipan", "ChST-10",
        "Pacific/Samoa", "SST11",
        "US/Alaska", "AKST9AKDT,M3.2.0,M11.1.0",
        "US/Aleutian", "HST10HDT,M3.2.0,M11.1.0",
        "US/Arizona", "MST7",
        "US/Central", "CST6CDT,M3.2.0,M11.1.0",
        "US/Eastern", "EST5EDT,M3.2.0,M11.1.0",
        "US/East-Indiana", "EST5EDT,M3.2.0,M11.1.0",
        "US/Hawaii", "HST10",
        "US/Indiana-Starke", "CST6CDT,M3.2.0,M11.1.0",
        "US/Michigan", "EST5EDT,M3.2.0,M11.1.0",
        "US/Mountain", "MST7MDT,M3.2.0,M11.1.0",
        "US/Pacific", "PST8PDT,M3.2.0,M11.1.0",
        "US/Samoa", "SST11",
        0, 0
};

char *zoneinfo_build_region_list()
{
    struct vpool vp;
    vpool_init(&vp, 1024, 0);

    int i = 0;
    char buf[32];
    bzero(buf, sizeof(buf));

    while(zoneinfo_data[i]) {
        const char *p = zoneinfo_data[i];
        char *q = strchr(p, '/');
        if (buf[0] == '\0' || strncmp(buf, p, q - p) != 0) {
            strncpy(buf, p, q - p);
            buf[q - p] = '\0';
            vpool_insert(&vp, vpool_get_length(&vp), buf, strlen(buf));
            vpool_insert(&vp, vpool_get_length(&vp), "\n", 1);
        }
        i += 2;
    }

    char *list = (char *) vpool_get_buf(&vp);
    size_t len = vpool_get_length(&vp);
    list[len - 1] = '\0';

    char *result = strdup(list);

    vpool_final(&vp);

    return result;
}

char *zoneinfo_build_region_zone_list(const char *region)
{
    struct vpool vp;
    vpool_init(&vp, 1024, 0);

    int i = 0;
    char buf[128];
    bzero(buf, sizeof(buf));

    int region_len = strlen(region);

    while(zoneinfo_data[i]) {
        const char *p = zoneinfo_data[i];
        char *q = strchr(p, '/');
        if (region_len == (q - p) && strncmp(region, p, region_len) == 0) {
            strcpy(buf, q + 1);
            vpool_insert(&vp, vpool_get_length(&vp), buf, strlen(buf));
            vpool_insert(&vp, vpool_get_length(&vp), "\n", 1);
        }
        i += 2;
    }

    char *result;
    size_t len = vpool_get_length(&vp);

    if (len > 0) {
        char *list = (char *) vpool_get_buf(&vp);
        list[len - 1] = '\0';
        result = strdup(list);
    } else {
        result = 0;
    }

    vpool_final(&vp);

    return result;
}

const char *zoneinfo_get_tz(const char *zone)
{
    int i = 0;
    while(zoneinfo_data[i]) {
        if (strcmp(zone, zoneinfo_data[i]) == 0) {
            return zoneinfo_data[i + 1];
        }
        i += 2;
    }
    return 0;
}
