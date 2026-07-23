#include "NetworkService.h"

#include "WebPage.h"

#include <string.h>


NetworkService* NetworkService::_instance =
    nullptr;


NetworkService::NetworkService(
    ESP8266WebServer& webServer,
    WebSocketsServer& webSocket,
    WebSocketInput& input,
    WebSocketDisplay& display,
    CommandLed& commandLed
)
:
_webServer(webServer),
_webSocket(webSocket),
_input(input),
_display(display),
_commandLed(commandLed)
{

    _instance =
        this;

}


bool NetworkService::beginStation(
    const char* ssid,
    const char* password,
    uint32_t timeout
)
{

    WiFi.mode(
        WIFI_STA
    );


    WiFi.begin(
        ssid,
        password
    );


    Serial.println();


    Serial.print(
        F("Conectando à rede ")
    );


    Serial.println(
        ssid
    );


    const uint32_t startTime =
        millis();


    while(
        WiFi.status() != WL_CONNECTED &&
        millis() - startTime < timeout
    )
    {

        delay(
            250
        );


        Serial.print(
            '.'
        );


        yield();

    }


    Serial.println();


    if(
        WiFi.status() != WL_CONNECTED
    )
    {

        Serial.println(
            F("Falha ao conectar ao Wi-Fi.")
        );


        return false;

    }


    Serial.println(
        F("Wi-Fi conectado.")
    );


    Serial.print(
        F("IP: http://")
    );


    Serial.println(
        WiFi.localIP()
    );


    return true;

}


bool NetworkService::beginAccessPoint(
    const char* ssid,
    const char* password
)
{

    WiFi.mode(
        WIFI_AP
    );


    const bool started =
        WiFi.softAP(
            ssid,
            password
        );


    Serial.println();


    Serial.print(
        F("Access Point: ")
    );


    Serial.println(
        started
        ?
        F("iniciado")
        :
        F("falhou")
    );


    if(started)
    {

        Serial.print(
            F("IP: http://")
        );


        Serial.println(
            WiFi.softAPIP()
        );

    }


    return started;

}


void NetworkService::beginServers()
{

    configureHttpServer();


    _webServer.begin();


    /*
     * Esta chamada estava ausente no código enviado.
     */
    _webSocket.begin();


    _webSocket.onEvent(
        webSocketCallback
    );


    Serial.println(
        F("Servidor HTTP iniciado.")
    );


    Serial.println(
        F("Servidor WebSocket iniciado.")
    );

}


void NetworkService::update()
{

    _webServer.handleClient();


    _webSocket.loop();

}


void NetworkService::configureHttpServer()
{

    _webServer.on(
        "/",
        HTTP_GET,
        [this]()
        {

            _webServer.send_P(
                200,
                PSTR(
                    "text/html; charset=utf-8"
                ),
                WEB_PAGE
            );

        }
    );


    _webServer.onNotFound(
        [this]()
        {

            _webServer.send(
                404,
                "text/plain",
                "Nao encontrado"
            );

        }
    );

}


void NetworkService::webSocketCallback(
    uint8_t clientNumber,
    WStype_t type,
    uint8_t* payload,
    size_t length
)
{

    if(!_instance)
        return;


    _instance->handleWebSocketEvent(
        clientNumber,
        type,
        payload,
        length
    );

}


void NetworkService::handleWebSocketEvent(
    uint8_t clientNumber,
    WStype_t type,
    uint8_t* payload,
    size_t length
)
{

    switch(type)
    {

        case WStype_CONNECTED:

            Serial.print(
                F(
                    "[WebSocket] Cliente conectado: "
                )
            );


            Serial.println(
                clientNumber
            );


            _display.sendCurrentState(
                clientNumber
            );

        break;


        case WStype_DISCONNECTED:

            Serial.print(
                F(
                    "[WebSocket] Cliente desconectado: "
                )
            );


            Serial.println(
                clientNumber
            );

        break;


        case WStype_TEXT:
        {

            char command[
                16
            ];


            size_t copyLength =
                length;


            if(
                copyLength >=
                sizeof(command)
            )
            {

                copyLength =
                    sizeof(command) - 1;

            }


            memcpy(
                command,
                payload,
                copyLength
            );


            command[
                copyLength
            ] =
                '\0';


            if(
                strcmp(
                    command,
                    "STATE"
                ) == 0
            )
            {

                _display.sendCurrentState(
                    clientNumber
                );


                break;

            }


            const bool accepted =
                _input.command(
                    command
                );


            if(accepted)
            {

                _commandLed.blink();

            }


            Serial.print(
                F(
                    "[WebSocket] Comando: "
                )
            );


            Serial.print(
                command
            );


            Serial.print(
                F(" - ")
            );


            Serial.println(
                accepted
                ?
                F("aceito")
                :
                F("ignorado")
            );

        }
        break;


        default:

        break;

    }

}