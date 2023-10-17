#include "lighting.h"
#include "stdint.h"

#ifdef ENABLE_RGB_MATRIX_COLOR_CHIPS

#ifndef MONO_BACKLIGHT_COLOR_1
#define MONO_BACKLIGHT_COLOR_1 { .h = 0, .s = 255 }
#endif

#include "via.h" // uses EEPROM address, lighting value IDs
#define RGB_LIGHT_CONFIG_EEPROM_ADDR (VIA_EEPROM_CUSTOM_CONFIG_ADDR)

#define PALETTE_HSV_BLUE { .h = 170, .s = 255} // RGB #0d07ff
#define PALETTE_HSV_RED { .h = 1, .s = 254} // RGB #ff0600
#define PALETTE_HSV_ORANGE { .h = 13, .s = 252} // RGB #ff5603
#define PALETTE_HSV_YELLOW { .h = 41, .s = 245} // RGB #fff60a
#define PALETTE_HSV_GREEN { .h = 102, .s = 252} // RGB #03ff68
#define PALETTE_HSV_PURPLE { .h = 197, .s = 255} // RGB #a200ff

pearls_palette_lighting_config light_config = {
    .layer_1_indicator_color = MONO_BACKLIGHT_COLOR_1,
    .layer_2_indicator_color = MONO_BACKLIGHT_COLOR_1,
    .layer_3_indicator_color = MONO_BACKLIGHT_COLOR_1,
    .matrix_01_color = PALETTE_HSV_ORANGE,
    .matrix_02_color = PALETTE_HSV_YELLOW,
    .matrix_03_color = PALETTE_HSV_GREEN,
    .matrix_04_color = PALETTE_HSV_RED,
    .matrix_05_color = PALETTE_HSV_BLUE,
    .matrix_06_color = PALETTE_HSV_PURPLE,
    .matrix_07_color = PALETTE_HSV_RED,
    .matrix_08_color = PALETTE_HSV_PURPLE,
    .matrix_09_color = PALETTE_HSV_ORANGE,
    .matrix_10_color = PALETTE_HSV_GREEN,
    .matrix_11_color = PALETTE_HSV_BLUE,
    .matrix_12_color = PALETTE_HSV_YELLOW,
    .layer_indicator_brightness = 150,
};

void _set_color( HS *color, uint8_t *data )
{
    color->h = data[0];
    color->s = data[1];
}

void _get_color( HS *color, uint8_t *data )
{
    data[0] = color->h;
    data[1] = color->s;
}

void pearls_palette_lighting_config_set_value( uint8_t *data )
{
    uint8_t *value_id = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch ( *value_id )
    {
        case id_layer_1_indicator_color:
        {
            _set_color( &(light_config.layer_1_indicator_color), value_data );
            break;
        }
        case id_layer_2_indicator_color:
        {
            _set_color( &(light_config.layer_2_indicator_color), value_data );
            break;
        }
        case id_layer_3_indicator_color:
        {
            _set_color( &(light_config.layer_3_indicator_color), value_data );
            break;
        }
        case id_matrix_01_color:
        {
            _set_color( &(light_config.matrix_01_color), value_data );
            break;
        }
        case id_matrix_02_color:
        {
            _set_color( &(light_config.matrix_02_color), value_data );
            break;
        }
        case id_matrix_03_color:
        {
            _set_color( &(light_config.matrix_03_color), value_data );
            break;
        }
        case id_matrix_04_color:
        {
            _set_color( &(light_config.matrix_04_color), value_data );
            break;
        }
        case id_matrix_05_color:
        {
            _set_color( &(light_config.matrix_05_color), value_data );
            break;
        }
        case id_matrix_06_color:
        {
            _set_color( &(light_config.matrix_06_color), value_data );
            break;
        }
        case id_matrix_07_color:
        {
            _set_color( &(light_config.matrix_07_color), value_data );
            break;
        }
        case id_matrix_08_color:
        {
            _set_color( &(light_config.matrix_08_color), value_data );
            break;
        }
        case id_matrix_09_color:
        {
            _set_color( &(light_config.matrix_09_color), value_data );
            break;
        }
        case id_matrix_10_color:
        {
            _set_color( &(light_config.matrix_10_color), value_data );
            break;
        }
        case id_matrix_11_color:
        {
            _set_color( &(light_config.matrix_11_color), value_data );
            break;
        }
        case id_matrix_12_color:
        {
            _set_color( &(light_config.matrix_12_color), value_data );
            break;
        }
        case id_layer_indicator_brightness:
        {
            light_config.layer_indicator_brightness = *value_data;
            break;
        }
    }
}

void pearls_palette_lighting_config_get_value( uint8_t *data )
{
    uint8_t *value_id = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch ( *value_id )
    {
        case id_layer_1_indicator_color:
        {
            _get_color( &(light_config.layer_1_indicator_color), value_data );
            break;
        }
        case id_layer_2_indicator_color:
        {
            _get_color( &(light_config.layer_2_indicator_color), value_data );
            break;
        }
        case id_layer_3_indicator_color:
        {
            _get_color( &(light_config.layer_3_indicator_color), value_data );
            break;
        }
        case id_matrix_01_color:
        {
            _get_color( &(light_config.matrix_01_color), value_data );
            break;
        }
        case id_matrix_02_color:
        {
            _get_color( &(light_config.matrix_02_color), value_data );
            break;
        }
        case id_matrix_03_color:
        {
            _get_color( &(light_config.matrix_03_color), value_data );
            break;
        }
        case id_matrix_04_color:
        {
            _get_color( &(light_config.matrix_04_color), value_data );
            break;
        }
        case id_matrix_05_color:
        {
            _get_color( &(light_config.matrix_05_color), value_data );
            break;
        }
        case id_matrix_06_color:
        {
            _get_color( &(light_config.matrix_06_color), value_data );
            break;
        }
        case id_matrix_07_color:
        {
            _get_color( &(light_config.matrix_07_color), value_data );
            break;
        }
        case id_matrix_08_color:
        {
            _get_color( &(light_config.matrix_08_color), value_data );
            break;
        }
        case id_matrix_09_color:
        {
            _get_color( &(light_config.matrix_09_color), value_data );
            break;
        }
        case id_matrix_10_color:
        {
            _get_color( &(light_config.matrix_10_color), value_data );
            break;
        }
        case id_matrix_11_color:
        {
            _get_color( &(light_config.matrix_11_color), value_data );
            break;
        }
        case id_matrix_12_color:
        {
            _get_color( &(light_config.matrix_12_color), value_data );
            break;
        }
        case id_layer_indicator_brightness:
        {
            *value_data = light_config.layer_indicator_brightness;
            break;
        }
    }
}

#endif


#ifdef VIA_ENABLE

void pearls_palette_lighting_config_load(void)
{
    eeprom_read_block( &light_config, ((void*)RGB_LIGHT_CONFIG_EEPROM_ADDR), sizeof(pearls_palette_lighting_config) );
}

// Save the data to persistent memory after changes are made
void pearls_palette_lighting_config_save(void) {
    eeprom_update_block( &light_config, ((void*)RGB_LIGHT_CONFIG_EEPROM_ADDR), sizeof(pearls_palette_lighting_config) );
}
void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if ( *channel_id == id_custom_channel ) {
        switch ( *command_id )
        {
            case id_custom_set_value:
            {
                pearls_palette_lighting_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value:
            {
                pearls_palette_lighting_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save:
            {
                // *command_id = id_unhandled;
                pearls_palette_lighting_config_save();
                break;
            }
            default:
            {
                // Unhandled message.
                *command_id = id_unhandled;
                break;
            }
        }
        return;
    }
}


void via_init_kb(void)
{
    // This checks both an EEPROM reset (from bootmagic lite, keycodes)
    // and also firmware build date (from via_eeprom_is_valid())
    if (eeconfig_is_enabled()) {
        pearls_palette_lighting_config_load();
    } else	{
        // If the EEPROM has not been saved before, or is out of date,
        // save the default values to the EEPROM. Default values
        // come from construction of the backlight_config instance.
        pearls_palette_lighting_config_save();
    }

}
void matrix_init_kb(void)
{
    // If VIA is disabled, we still need to load backlight settings.
    // Call via_init_kb() the same way as via_init(), with setting
    // EEPROM valid afterwards.
#ifndef VIA_ENABLE
    via_init_kb();
    via_eeprom_set_valid(true);
#endif // VIA_ENABLE

    matrix_init_user();
}

#endif 
