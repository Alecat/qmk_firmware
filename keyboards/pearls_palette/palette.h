#pragma once

enum via_light_config {
    id_layer_indicator_color = 1,
    id_matrix_color = 2,
    id_layer_indicator_brightness = 3
};


typedef struct PACKED
{
    uint8_t h;
    uint8_t s;
} HS;

// TODO can we store arrays in the eeprom for the matrix colours
typedef struct
{
    HS layer_indicator_color[4];
    HS matrix_color[12];
    uint8_t layer_indicator_brightness;
} pearls_palette_lighting_config;
