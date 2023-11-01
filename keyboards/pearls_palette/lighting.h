#pragma once

#include "quantum.h"

enum via_light_config {
    id_matrix_color = 1,
    id_layer_indicator_color = 2,
    id_layer_indicator_brightness = 3,
};

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
// TODO how to avoid repeated declarations

void pearls_palette_lighting_config_set_value( uint8_t *data );
void pearls_palette_lighting_config_get_value( uint8_t *data );
extern uint8_t g_rgb_frame_buffer[MATRIX_ROWS][MATRIX_COLS];
