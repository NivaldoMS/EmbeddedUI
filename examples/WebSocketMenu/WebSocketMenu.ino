#include <Arduino.h>

#include <ESP8266WebServer.h>

#include <WebSocketsServer.h>

#include "AppConfig.h"

#include "CommandLed.h"

#include "WebSocketInput.h"

#include "WebSocketDisplay.h"

#include "NetworkService.h"

#include "MenuApplication.h"


ESP8266WebServer webServer(
    AppConfig::HTTP_PORT
);


WebSocketsServer webSocket(
    AppConfig::WEBSOCKET_PORT
);


CommandLed commandLed(
    AppConfig::COMMAND_LED_PIN,
    AppConfig::COMMAND_LED_TIME
);


WebSocketInput webSocketInput;


WebSocketDisplay webSocketDisplay(
    webSocket,
    AppConfig::DISPLAY_WIDTH,
    AppConfig::DISPLAY_HEIGHT
);


NetworkService networkService(
    webServer,
    webSocket,
    webSocketInput,
    webSocketDisplay,
    commandLed
);


MenuApplication application(
    webSocketDisplay
);


void setup()
{

    Serial.begin(
        115200
    );


    commandLed.begin();


    delay(
        500
    );


    application.begin(
        webSocketInput
    );


    bool connected =
        false;


    if(
        AppConfig::USE_STATION_MODE
    )
    {

        connected =
            networkService.beginStation(
                AppConfig::WIFI_SSID,
                AppConfig::WIFI_PASSWORD,
                AppConfig::WIFI_TIMEOUT
            );

    }
    else
    {

        connected =
            networkService.beginAccessPoint(
                AppConfig::WIFI_SSID,
                AppConfig::WIFI_PASSWORD
            );

    }


    if(!connected)
    {

        Serial.println(
            F("Rede indisponível.")
        );


        return;

    }


    networkService.beginServers();

}


void loop()
{

    networkService.update();


    application.update();


    commandLed.update();


    yield();

}