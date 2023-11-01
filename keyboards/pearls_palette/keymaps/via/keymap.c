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
    HS matrix_color[12];
    HS layer_indicator_color[4];
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
        TO(1),  MO(3),  KC_LBRC,    KC_RBRC,
        C(KC_X),C(KC_C),C(KC_V),    KC_LALT,
        KC_B,   KC_V,   C(KC_S),    KC_LSFT,
        KC_E,   KC_M,   C(KC_Z),    C(KC_Y)
    ),
    [1] = LAYOUT(
        TO(2),  MO(3),  KC_LBRC,    KC_RBRC,
        G(KC_X),G(KC_C),G(KC_V),    KC_LALT,
        KC_B,   KC_V,   G(KC_S),    KC_LSFT,
        KC_E,   KC_M,   G(KC_Z),    LSG(KC_Z)
    ),
    [2] = LAYOUT(
        TO(0),  MO(3),  MI_TRSD,    MI_TRSU,
        MI_E,   MI_A,   MI_D1,      MI_G1,
        MI_D,   MI_G,   MI_C1,      MI_F1,
        MI_C,   MI_F,   MI_B,       MI_E1
    ),
    [3] = LAYOUT(
        KC_ESC, KC_NO,  KC_VOLD,    KC_VOLU,
        RGB_VAD,RGB_VAI,RGB_TOG,    KC_RALT,
        KC_MUTE,KC_MPLY,KC_UP,      KC_RSFT,
        KC_WWW_SEARCH, KC_LEFT, KC_DOWN, KC_RGHT
    )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =  { ENCODER_CCW_CW(KC_LBRC,    KC_RBRC) },
    [1] =  { ENCODER_CCW_CW(KC_LBRC,    KC_RBRC) },
    [2] =  { ENCODER_CCW_CW(MI_TRSD,    MI_TRSU) },
    [3] =  { ENCODER_CCW_CW(KC_VOLD,    KC_VOLU) }
};
#else
bool encoder_update_kb(uint8_t index, bool clockwise) {
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
    return false;
}
#endif


// Assume the keyboard has already been initialised
bool has_init = true;
void eeconfig_init_user(void) {  // EEPROM is getting reset!
    // Workaround since VIA compatibility seems to cause eeprom to be ignored
    // Details here, but we just set a flag instead of starting a timer
    // https://www.reddit.com/r/olkb/comments/9ny0jp/qmk_rgb_settings_done_in_matrix_init_user_are/
    has_init = false;
}

void keyboard_post_init_user(void) {
    if (!has_init) {
        rgb_matrix_enable();
        rgb_matrix_mode(RGB_MATRIX_CUSTOM_COLOR_CHIPS);
    }
    rgb_matrix_sethsv_noeeprom(rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v);
}

bool rgb_matrix_indicators_user(void) {
    uint8_t layer = get_highest_layer(layer_state);
    HSV hsv = {.h = light_config.layer_indicator_color[layer].h, .s = light_config.layer_indicator_color[layer].s, .v = light_config.layer_indicator_brightness };
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
