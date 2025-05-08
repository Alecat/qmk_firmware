// Copyright 2023 Alethea Lim (@Alecat)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

enum via_light_config {
    id_matrix_color = 1,
    id_layer_indicator_color = 2,
    id_layer_indicator_brightness = 3
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
