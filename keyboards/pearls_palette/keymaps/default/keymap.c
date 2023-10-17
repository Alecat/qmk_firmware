// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───────┐
     * │   │Enc│       │
     * ├───┼───┼───┬───┤
     * │ 1 │ 2 │ 3 │ 4 │
     * ├───┼───┼───┼───┤
     * │ 5 │ 6 │ 7 │ 8 │
     * ├───┼───┼───┼───┤
     * │ 9 │ 10│ 11│ 12│
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT(
        TO(1),   MO(1),
        KC_F1,   KC_F2,   KC_F3,   KC_F4,
        KC_F5,   KC_F6,   KC_F7,   KC_F8,
        KC_F9,   KC_F10,  KC_F11,  KC_F12
    ),
    [1] = LAYOUT(
        TO(0),   MO(0),
        KC_LSFT,   RGB_MOD,   KC_F3,   KC_F4,
        KC_LCTL,   KC_F6,   KC_F7,   KC_F8,
        KC_LALT,   KC_F10,  LGUI(KC_Z),  SGUI(KC_Z)
    )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] =  { ENCODER_CCW_CW(LGUI(KC_Z), SGUI(KC_Z)) }
};

bool rgb_matrix_indicators_user(void) {
    uint8_t layer = get_highest_layer(layer_state);
    if (layer == 0) {
        rgb_matrix_set_color(0, 0xFF, 0xFF, 0xFF);
    }
    if (layer == 1) {
        rgb_matrix_set_color(0, 0xFF, 0x00, 0xFF);
    }
    return false;
}