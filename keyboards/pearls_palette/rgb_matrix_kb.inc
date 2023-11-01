// Copyright 2023 Alethea Lim (@Alecat)
// SPDX-License-Identifier: GPL-2.0-or-later

#ifdef ENABLE_RGB_MATRIX_COLOR_CHIPS
RGB_MATRIX_EFFECT(COLOR_CHIPS)

#   ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

typedef struct PACKED
{
    uint8_t h;
    uint8_t s;
} HS;

typedef struct
{
    HS matrix_color[12];
    HS layer_indicator_color[4];
    uint8_t layer_indicator_brightness;
} pearls_palette_lighting_config;

extern pearls_palette_lighting_config light_config;

// Track keypresses as they happen - this is updated in process_record_user
bool led_keys_pressed[13] = {};

static bool COLOR_CHIPS(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    // Skip the first row
    for (uint8_t row = 1; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint8_t position_index = g_led_config.matrix_co[row][col];
            if (position_index != NO_LED) {
                uint8_t config_index = (row-1) * (MATRIX_COLS) + col;
                HSV hsv = {
                    .h = light_config.matrix_color[config_index].h,
                    .s = light_config.matrix_color[config_index].s,
                    .v = rgb_matrix_config.hsv.v
                };
                if (led_keys_pressed[position_index]) {
                    hsv.s = hsv.s / 2;
                }
                RGB rgb = hsv_to_rgb(hsv);
                rgb_matrix_set_color(position_index, rgb.r, rgb.g, rgb.b);
            }
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#   endif


#endif // ENABLE_RGB_MATRIX_COLOR_CHIPS