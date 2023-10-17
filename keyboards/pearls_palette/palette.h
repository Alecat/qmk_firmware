#pragma once

enum via_light_config {
    id_layer_1_indicator_color = 1,
    id_layer_2_indicator_color = 2,
    id_layer_3_indicator_color = 3,
    id_matrix_01_color = 4,
    id_matrix_02_color = 5,
    id_matrix_03_color = 6,
    id_matrix_04_color = 7,
    id_matrix_05_color = 8,
    id_matrix_06_color = 9,
    id_matrix_07_color = 10,
    id_matrix_08_color = 11,
    id_matrix_09_color = 12,
    id_matrix_10_color = 13,
    id_matrix_11_color = 14,
    id_matrix_12_color = 15,
    id_layer_indicator_brightness = 16,
    id_matrix_brightness = 17
};


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
