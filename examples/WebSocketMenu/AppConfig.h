#ifndef EMBEDDED_UI_APP_CONFIG_H
#define EMBEDDED_UI_APP_CONFIG_H


#include <Arduino.h>


namespace AppConfig
{


/*
 * Rede Wi-Fi.
 */
static constexpr const char* WIFI_SSID =
    "NMS";


static constexpr const char* WIFI_PASSWORD =
    "*1234567*";


/*
 * true:
 * conecta ao roteador existente.
 *
 * false:
 * cria um Access Point.
 */
static constexpr bool USE_STATION_MODE =
    true;


/*
 * Portas dos servidores.
 */
static constexpr uint16_t HTTP_PORT =
    80;


static constexpr uint16_t WEBSOCKET_PORT =
    81;


/*
 * Tempo máximo para conexão em modo Station.
 */
static constexpr uint32_t WIFI_TIMEOUT =
    20000;


/*
 * LED de confirmação de comando.
 */
static constexpr uint8_t COMMAND_LED_PIN =
    LED_BUILTIN;


static constexpr uint16_t COMMAND_LED_TIME =
    60;


/*
 * Dimensões lógicas do display.
 */
static constexpr uint16_t DISPLAY_WIDTH =
    128;


static constexpr uint16_t DISPLAY_HEIGHT =
    128;


}


#endif