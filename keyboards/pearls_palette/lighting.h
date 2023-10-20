#pragma once

#include "quantum.h"

enum via_light_config {
    id_layer_indicator_color = 1,
    id_matrix_color = 2,
    id_layer_indicator_brightness = 3,
};

typedef struct PACKED
{
    uint8_t h;
    uint8_t s;
} HS;

typedef struct
{
    HS layer_indicator_color[4];
    HS matrix_color[12];
    uint8_t layer_indicator_brightness;
} pearls_palette_lighting_config;

void pearls_palette_lighting_config_set_value( uint8_t *data );
void pearls_palette_lighting_config_get_value( uint8_t *data );
extern uint8_t g_rgb_frame_buffer[MATRIX_ROWS][MATRIX_COLS];
