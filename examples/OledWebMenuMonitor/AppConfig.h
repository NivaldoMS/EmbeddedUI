#ifndef OLED_WEB_MENU_MONITOR_APP_CONFIG_H
#define OLED_WEB_MENU_MONITOR_APP_CONFIG_H


#include <Arduino.h>


namespace AppConfig
{


/*
 * Rede Wi-Fi 2,4 GHz.
 */
static constexpr const char* WIFI_SSID =
    "NMS";


static constexpr const char* WIFI_PASSWORD =
    "*1234567*";


/*
 * Servidores.
 */
static constexpr uint16_t HTTP_PORT =
    80;


static constexpr uint16_t WEBSOCKET_PORT =
    81;


static constexpr uint32_t WIFI_TIMEOUT =
    30000;


/*
 * Interface I2C.
 */
static constexpr uint8_t I2C_SDA_PIN =
    D2;


static constexpr uint8_t I2C_SCL_PIN =
    D1;


/*
 * Botões físicos.
 *
 * Cada botão deve ser conectado
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
 * LED de atividade WebSocket.
 */
static constexpr uint8_t ACTIVITY_LED_PIN =
    LED_BUILTIN;


static constexpr uint16_t ACTIVITY_LED_DURATION =
    60;


}


#endif