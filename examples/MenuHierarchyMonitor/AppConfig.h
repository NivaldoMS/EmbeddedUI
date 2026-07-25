#ifndef MENU_HIERARCHY_MONITOR_APP_CONFIG_H
#define MENU_HIERARCHY_MONITOR_APP_CONFIG_H


#include <Arduino.h>


namespace AppConfig
{


static constexpr const char* WIFI_SSID =
    "NMS";


static constexpr const char* WIFI_PASSWORD =
    "*1234567*";


static constexpr uint16_t HTTP_PORT =
    80;


static constexpr uint16_t WEBSOCKET_PORT =
    81;


static constexpr uint32_t WIFI_TIMEOUT =
    30000;


/*
 * Botões físicos.
 *
 * Cada botão deve ser ligado
 * entre o pino e GND.
 */
static constexpr uint8_t BUTTON_CW_PIN =
    D5;


static constexpr uint8_t BUTTON_CCW_PIN =
    D6;


static constexpr uint8_t BUTTON_ENTER_PIN =
    D7;


static constexpr uint8_t BUTTON_BACK_PIN =
    D3;


/*
 * LED de atividade.
 */
static constexpr uint8_t COMMAND_LED_PIN =
    LED_BUILTIN;


static constexpr uint16_t COMMAND_LED_DURATION =
    60;


/*
 * Dimensões lógicas usadas pelo Renderer.
 */
static constexpr uint16_t VIRTUAL_DISPLAY_WIDTH =
    128;


static constexpr uint16_t VIRTUAL_DISPLAY_HEIGHT =
    64;


}


#endif