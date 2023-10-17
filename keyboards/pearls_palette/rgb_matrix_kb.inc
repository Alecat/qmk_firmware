#ifdef ENABLE_RGB_MATRIX_COLOR_CHIPS
RGB_MATRIX_EFFECT(COLOR_CHIPS)

#   ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

typedef struct PACKED
{
    uint8_t h;
    uint8_t s;
} HS;

// TODO can we store arrays in the eeprom for the matrix colours
typedef struct
{
    HS layer_1_indicator_color;
    HS layer_2_indicator_color;
    HS layer_3_indicator_color;
    HS matrix_01_color;
    HS matrix_02_color;
    HS matrix_03_color;
    HS matrix_04_color;
    HS matrix_05_color;
    HS matrix_06_color;
    HS matrix_07_color;
    HS matrix_08_color;
    HS matrix_09_color;
    HS matrix_10_color;
    HS matrix_11_color;
    HS matrix_12_color;
    uint8_t layer_indicator_brightness;
} pearls_palette_lighting_config;

extern pearls_palette_lighting_config light_config;

// Track keypresses as they happen - this is updated in process_record_useraaaaaaa
bool led_keys_pressed[13] = {};

static bool COLOR_CHIPS(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    // Skip the first LED
    for (uint8_t i = 1; i < led_max; i++) {
        HSV hsv = {.h = 0, .s = 0, .v = rgb_matrix_config.hsv.v };
        uint8_t led_index = NO_LED;
        switch (i) {
            case 1: {
                hsv.h = light_config.matrix_01_color.h;
                hsv.s = light_config.matrix_01_color.s;
                led_index = g_led_config.matrix_co[1][0];
                break;
            }
            case 2: {
                hsv.h = light_config.matrix_02_color.h;
                hsv.s = light_config.matrix_02_color.s;
                led_index = g_led_config.matrix_co[1][1];
                break;
            }
            case 3: {
                hsv.h = light_config.matrix_03_color.h;
                hsv.s = light_config.matrix_03_color.s;
                led_index = g_led_config.matrix_co[1][2];
                break;
            }
            case 4: {
                hsv.h = light_config.matrix_04_color.h;
                hsv.s = light_config.matrix_04_color.s;
                led_index = g_led_config.matrix_co[1][3];
                break;
            }
            case 5: {
                hsv.h = light_config.matrix_05_color.h;
                hsv.s = light_config.matrix_05_color.s;
                led_index = g_led_config.matrix_co[2][0];
                break;
            }
            case 6: {
                hsv.h = light_config.matrix_06_color.h;
                hsv.s = light_config.matrix_06_color.s;
                led_index = g_led_config.matrix_co[2][1];
                break;
            }
            case 7: {
                hsv.h = light_config.matrix_07_color.h;
                hsv.s = light_config.matrix_07_color.s;
                led_index = g_led_config.matrix_co[2][2];
                break;
            }
            case 8: {
                hsv.h = light_config.matrix_08_color.h;
                hsv.s = light_config.matrix_08_color.s;
                led_index = g_led_config.matrix_co[2][3];
                break;
            }
            case 9: {
                hsv.h = light_config.matrix_09_color.h;
                hsv.s = light_config.matrix_09_color.s;
                led_index = g_led_config.matrix_co[3][0];
                break;
            }
            case 10: {
                hsv.h = light_config.matrix_10_color.h;
                hsv.s = light_config.matrix_10_color.s;
                led_index = g_led_config.matrix_co[3][1];
                break;
            }
            case 11: {
                hsv.h = light_config.matrix_11_color.h;
                hsv.s = light_config.matrix_11_color.s;
                led_index = g_led_config.matrix_co[3][2];
                break;
            }
            case 12: {
                hsv.h = light_config.matrix_12_color.h;
                hsv.s = light_config.matrix_12_color.s;
                led_index = g_led_config.matrix_co[3][3];
                break;
            }
        }
        if (led_index != NO_LED) {
            if (led_keys_pressed[led_index]) {
                hsv.s = hsv.s / 2;
            }
            RGB rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(led_index, rgb.r, rgb.g, rgb.b);
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#   endif


#endif // ENABLE_RGB_MATRIX_COLOR_CHIPS