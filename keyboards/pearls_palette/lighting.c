#include "lighting.h"
#include "stdint.h"

#ifdef ENABLE_RGB_MATRIX_COLOR_CHIPS

#include "via.h" // uses EEPROM address, lighting value IDs
#define RGB_LIGHT_CONFIG_EEPROM_ADDR (VIA_EEPROM_CUSTOM_CONFIG_ADDR)

#define PALETTE_HSV_WHITE { .h = 0, .s = 0 }
#define PALETTE_HSV_RED { .h = 1, .s = 254} // RGB #ff0600
#define PALETTE_HSV_ORANGE { .h = 13, .s = 252} // RGB #ff5603
#define PALETTE_HSV_YELLOW { .h = 41, .s = 245} // RGB #fff60a
#define PALETTE_HSV_GREEN { .h = 91, .s = 252} // RGB #03ff68
#define PALETTE_HSV_TEAL { .h = 102, .s = 252} // RGB #03ff68
#define PALETTE_HSV_BLUE { .h = 170, .s = 255} // RGB #0d07ff
#define PALETTE_HSV_PURPLE { .h = 197, .s = 255} // RGB #a200ff
#define PALETTE_HSV_PINK { .h = 227, .s = 226 } // RGB #ff12a9

pearls_palette_lighting_config light_config = {
    .layer_indicator_color[0] = PALETTE_HSV_PINK,
    .layer_indicator_color[1] = PALETTE_HSV_PURPLE,
    .layer_indicator_color[2] = PALETTE_HSV_GREEN,
    .layer_indicator_color[3] = PALETTE_HSV_WHITE,
    .matrix_color[0] = PALETTE_HSV_ORANGE,
    .matrix_color[1] = PALETTE_HSV_YELLOW,
    .matrix_color[2] = PALETTE_HSV_TEAL,
    .matrix_color[3] = PALETTE_HSV_RED,
    .matrix_color[4] = PALETTE_HSV_BLUE,
    .matrix_color[5] = PALETTE_HSV_PURPLE,
    .matrix_color[6] = PALETTE_HSV_RED,
    .matrix_color[7] = PALETTE_HSV_PURPLE,
    .matrix_color[8] = PALETTE_HSV_ORANGE,
    .matrix_color[9] = PALETTE_HSV_TEAL,
    .matrix_color[10] = PALETTE_HSV_BLUE,
    .matrix_color[11] = PALETTE_HSV_YELLOW,
    .layer_indicator_brightness = 200,
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
        case id_layer_indicator_color:
        {
            uint8_t layer_index = value_data[0];
            _set_color( &(light_config.layer_indicator_color[layer_index]), &(value_data[1]) );
            break;
        }
        case id_matrix_color:
        {
            uint8_t led_position = value_data[0] - 1;
            _set_color( &(light_config.matrix_color[led_position]), &(value_data[1]) );
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
        case id_layer_indicator_color:
        {
            uint8_t layer_index = value_data[0];
            _get_color( &(light_config.layer_indicator_color[layer_index]), &(value_data[1]) );
            break;
        }
        case id_matrix_color:
        {

            uint8_t led_position = value_data[0] - 1;
            _get_color( &(light_config.matrix_color[led_position]), &(value_data[1]) );
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
