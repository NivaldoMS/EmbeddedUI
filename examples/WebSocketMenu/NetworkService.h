#ifndef EMBEDDED_UI_NETWORK_SERVICE_H
#define EMBEDDED_UI_NETWORK_SERVICE_H


#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include <WebSocketsServer.h>

#include "WebSocketInput.h"
#include "WebSocketDisplay.h"
#include "CommandLed.h"


class NetworkService
{

public:


    NetworkService(
        ESP8266WebServer& webServer,
        WebSocketsServer& webSocket,
        WebSocketInput& input,
        WebSocketDisplay& display,
        CommandLed& commandLed
    );


    bool beginStation(
        const char* ssid,
        const char* password,
        uint32_t timeout
    );


    bool beginAccessPoint(
        const char* ssid,
        const char* password
    );


    void beginServers();


    void update();


private:


    void configureHttpServer();


    void handleWebSocketEvent(
        uint8_t clientNumber,
        WStype_t type,
        uint8_t* payload,
        size_t length
    );


    static void webSocketCallback(
        uint8_t clientNumber,
        WStype_t type,
        uint8_t* payload,
        size_t length
    );


    static NetworkService* _instance;


    ESP8266WebServer& _webServer;


    WebSocketsServer& _webSocket;


    WebSocketInput& _input;


    WebSocketDisplay& _display;


    CommandLed& _commandLed;


};


#endif