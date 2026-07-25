#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include <WebSocketsServer.h>

#include <EmbeddedUI.h>

#include <drivers/display/NullDisplay.h>

#include <utilities/CommandLed.h>

#include <extensions/websocket/WebSocketInput.h>
#include <extensions/websocket/MenuHierarchyPublisher.h>

#include "AppConfig.h"
#include "WebPage.h"
#include "MenuApplication.h"

#include <string.h>


using namespace EmbeddedUI;


/*
 * Servidor HTTP.
 */
ESP8266WebServer webServer(
    AppConfig::HTTP_PORT
);


/*
 * Servidor WebSocket.
 */
WebSocketsServer webSocket(
    AppConfig::WEBSOCKET_PORT
);


/*
 * Entrada remota.
 */
WebSocketInput webSocketInput;


/*
 * Driver sem saída gráfica.
 */
NullDisplay nullDisplay(
    AppConfig::VIRTUAL_DISPLAY_WIDTH,
    AppConfig::VIRTUAL_DISPLAY_HEIGHT
);


/*
 * Aplicação de demonstração.
 */
MenuApplication application(
    nullDisplay
);


/*
 * Publicação da árvore do menu.
 *
 * O objeto Menu já existe no construtor
 * de MenuApplication, mesmo antes de begin().
 */
MenuHierarchyPublisher hierarchyPublisher(
    webSocket,
    application.menu()
);


/*
 * LED indicador de comando.
 */
CommandLed commandLed(
    AppConfig::COMMAND_LED_PIN,
    AppConfig::COMMAND_LED_DURATION,
    true
);


bool connectToWiFi()
{

    WiFi.mode(
        WIFI_STA
    );


    WiFi.disconnect();


    delay(
        200
    );


    Serial.println();


    Serial.print(
        F("Conectando à rede ")
    );


    Serial.println(
        AppConfig::WIFI_SSID
    );


    WiFi.begin(
        AppConfig::WIFI_SSID,
        AppConfig::WIFI_PASSWORD
    );


    const uint32_t startedAt =
        millis();


    while(
        WiFi.status() != WL_CONNECTED &&
        millis() - startedAt <
            AppConfig::WIFI_TIMEOUT
    )
    {

        Serial.print(
            '.'
        );


        delay(
            250
        );


        yield();

    }


    Serial.println();


    if(
        WiFi.status() != WL_CONNECTED
    )
    {

        Serial.print(
            F("Falha ao conectar. Status: ")
        );


        Serial.println(
            static_cast<int>(
                WiFi.status()
            )
        );


        WiFi.printDiag(
            Serial
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


void configureHttpServer()
{

    webServer.on(
        "/",
        HTTP_GET,
        []()
        {

            webServer.send_P(
                200,
                PSTR(
                    "text/html; charset=utf-8"
                ),
                WEB_PAGE
            );

        }
    );


    webServer.onNotFound(
        []()
        {

            webServer.send(
                404,
                "text/plain",
                "Nao encontrado"
            );

        }
    );

}


void handleWebSocketEvent(
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


            hierarchyPublisher.sendCurrentState(
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

                hierarchyPublisher.sendCurrentState(
                    clientNumber
                );


                break;

            }


            const bool accepted =
                webSocketInput.command(
                    command
                );


            if(accepted)
            {

                commandLed.blink();

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


void setup()
{

    Serial.begin(
        115200
    );


    delay(
        300
    );


    commandLed.begin();


    application.begin(
        webSocketInput
    );


    if(!connectToWiFi())
    {

        Serial.println(
            F("Aplicação iniciada sem rede.")
        );


        return;

    }


    configureHttpServer();


    webServer.begin();


    webSocket.begin();


    webSocket.onEvent(
        handleWebSocketEvent
    );


    hierarchyPublisher.forcePublish();


    Serial.println(
        F("Servidor HTTP iniciado na porta 80.")
    );


    Serial.println(
        F("WebSocket iniciado na porta 81.")
    );

}


void loop()
{

    webServer.handleClient();


    webSocket.loop();


    application.update();


    /*
     * Compara o JSON atual com o anterior.
     * Só transmite quando há alguma alteração.
     */
    hierarchyPublisher.update();


    commandLed.update();


    yield();

}