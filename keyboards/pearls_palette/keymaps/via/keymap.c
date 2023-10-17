// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

typedef struct PACKED
{
    uint8_t h;
    uint8_t s;
} HS;

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
extern bool led_keys_pressed[13];
bool encoder_pressed;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───────┐
     * │Lay│Enc│FakeEnc│
     * ├───┼───┼───┬───┤
     * │ 1 │ 2 │ 3 │ 4 │
     * ├───┼───┼───┼───┤
     * │ 5 │ 6 │ 7 │ 8 │
     * ├───┼───┼───┼───┤
     * │ 9 │ 10│ 11│ 12│
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT(
        TO(1),   MO(2),   KC_VOLU, KC_VOLD, 
        KC_F1,   KC_F2,   KC_F3,   KC_F4,
        KC_F5,   KC_F6,   KC_F7,   KC_F8,
        KC_F9,   KC_F10,  KC_F11,  KC_F12
    ),
    [1] = LAYOUT(
        TO(0),   MO(2),   SGUI(KC_Z), LGUI(KC_Z), 
        KC_LSFT,   RGB_MOD,   KC_F3,   KC_F4,
        KC_LCTL,   KC_F6,   KC_F7,   KC_F8,
        KC_LALT,   KC_F10,  LGUI(KC_Z),  SGUI(KC_Z)
    ),
    [2] = LAYOUT(
        KC_TRNS,   KC_TRNS,   RGB_VAI,     RGB_VAD,     
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS
    )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] =  { ENCODER_CCW_CW(LGUI(KC_Z), SGUI(KC_Z)) },
    [2] =  { ENCODER_CCW_CW(RGB_VAI, RGB_VAD) }
};
#else
bool encoder_update_user(uint8_t index, bool clockwise) {
    // if (index == 0) { /* First (only) encoder */
    if (encoder_pressed) {
        if (clockwise) {
            rgb_matrix_increase_val();
        }
        else {
            rgb_matrix_decrease_val();
        }
    }
    else {
        uint8_t layer = get_highest_layer(layer_state);
        if (clockwise) {
            tap_code16(dynamic_keymap_get_keycode(layer, 0, 2));
        } else {
            tap_code16(dynamic_keymap_get_keycode(layer, 0, 3));
        }
    }
    // }
    return false;
}
#endif

void eeconfig_init_user(void) {  // EEPROM is getting reset!
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_enable();
    rgb_matrix_mode(RGB_MATRIX_CUSTOM_COLOR_CHIPS);
#endif
}

bool rgb_matrix_indicators_user(void) {
    HSV hsv = {.h = 0, .s = 0, .v = light_config.layer_indicator_brightness };

    uint8_t layer = get_highest_layer(layer_state);

    if (layer == 0) {
        hsv.s = 0;
    }
    if (layer == 1) {
        hsv.h = light_config.layer_1_indicator_color.h;
        hsv.s = light_config.layer_1_indicator_color.s;
    }
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(0, rgb.r, rgb.g, rgb.b);

    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t led_index = g_led_config.matrix_co[record->event.key.row][record->event.key.col];

    if (record->event.key.row == 0 && record->event.key.col == 1) {
        // The encoder is being pressed
        encoder_pressed = record->event.pressed;
    }

    if (led_index != NO_LED) {
        led_keys_pressed[led_index] = record->event.pressed;
    }
    // let QMK process the keycode
    return true;
}
