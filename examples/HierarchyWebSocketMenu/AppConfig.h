#ifndef HIERARCHY_WEB_SOCKET_MENU_APP_CONFIG_H
#define HIERARCHY_WEB_SOCKET_MENU_APP_CONFIG_H


#include <Arduino.h>


namespace AppConfig
{


static constexpr const char* WIFI_SSID =
    "Nms";


static constexpr const char* WIFI_PASSWORD =
    "*1234567*";


static constexpr uint16_t HTTP_PORT =
    80;


static constexpr uint16_t WEBSOCKET_PORT =
    81;


static constexpr uint32_t WIFI_TIMEOUT =
    30000;


static constexpr uint8_t COMMAND_LED_PIN =
    LED_BUILTIN;


static constexpr uint16_t COMMAND_LED_DURATION =
    30;


static constexpr uint16_t VIRTUAL_DISPLAY_WIDTH =
    128;


static constexpr uint16_t VIRTUAL_DISPLAY_HEIGHT =
    64;


}


#endif