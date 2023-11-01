// Copyright 2023 Alethea Lim (@Alecat)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

#define RGB_MATRIX_LED_COUNT 13
#define RGB_MATRIX_KEYPRESSES

#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define ENABLE_RGB_MATRIX_COLOR_CHIPS
#define RGB_MATRIX_DEFAULT_VAL 100
#define RGB_MATRIX_DEFAULT_HUE 111
#define RGB_MATRIX_DEFAULT_SAT 173

#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 33

#define MIDI_ADVANCED