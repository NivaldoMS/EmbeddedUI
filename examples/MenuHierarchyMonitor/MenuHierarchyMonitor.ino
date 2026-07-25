#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include <WebSocketsServer.h>

#include <EmbeddedUI.h>

#include <drivers/display/NullDisplay.h>

#include <utilities/CommandLed.h>

#include <extensions/websocket/MenuHierarchyMonitor.h>

#include "AppConfig.h"
#include "WebPage.h"
#include "MenuApplication.h"

#include <string.h>


using namespace EmbeddedUI;


/*
 * Servidores.
 */
ESP8266WebServer webServer(
    AppConfig::HTTP_PORT
);


WebSocketsServer webSocket(
    AppConfig::WEBSOCKET_PORT
);


/*
 * Botões físicos.
 */
Buttons buttons(
    AppConfig::BUTTON_CW_PIN,
    AppConfig::BUTTON_CCW_PIN,
    AppConfig::BUTTON_ENTER_PIN,
    AppConfig::BUTTON_BACK_PIN
);


/*
 * Saída gráfica descartada.
 */
NullDisplay nullDisplay(
    AppConfig::VIRTUAL_DISPLAY_WIDTH,
    AppConfig::VIRTUAL_DISPLAY_HEIGHT
);


/*
 * Aplicação EmbeddedUI.
 */
MenuApplication application(
    nullDisplay
);


/*
 * Monitor WebSocket.
 */
MenuHierarchyMonitor hierarchyMonitor(
    webSocket,
    application.menu()
);


/*
 * LED indicador de atividade WebSocket.
 */
CommandLed activityLed(
    AppConfig::COMMAND_LED_PIN,
    AppConfig::COMMAND_LED_DURATION,
    true
);


bool networkReady =
    false;


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
        F("Monitor: http://")
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
                    "[Monitor] Cliente conectado: "
                )
            );


            Serial.println(
                clientNumber
            );


            hierarchyMonitor.sendCurrentState(
                clientNumber
            );


            activityLed.blink();

        break;


        case WStype_DISCONNECTED:

            Serial.print(
                F(
                    "[Monitor] Cliente desconectado: "
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


            /*
             * O monitor é passivo.
             *
             * O único comando aceito é STATE,
             * utilizado para solicitar o estado
             * inicial após a conexão.
             */
            if(
                strcmp(
                    command,
                    "STATE"
                ) == 0
            )
            {

                hierarchyMonitor.sendCurrentState(
                    clientNumber
                );


                activityLed.blink();

            }

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


    activityLed.begin();


    application.begin(
        buttons
    );


    networkReady =
        connectToWiFi();


    if(!networkReady)
    {

        Serial.println(
            F(
                "Menu iniciado sem o monitor de rede."
            )
        );


        return;

    }


    configureHttpServer();


    webServer.begin();


    webSocket.begin();


    webSocket.onEvent(
        handleWebSocketEvent
    );


    hierarchyMonitor.forcePublish();


    Serial.println(
        F(
            "Monitor hierárquico iniciado."
        )
    );

}


void loop()
{

    /*
     * A EmbeddedUI continua funcionando
     * mesmo sem rede.
     */
    application.update();


    if(networkReady)
    {

        webServer.handleClient();


        webSocket.loop();


        hierarchyMonitor.setSelectedNode(
            application.selectedNode()
        );


        hierarchyMonitor.setEditingNode(
            application.editingNode()
        );


        hierarchyMonitor.setExecutingNode(
            application.executingNode()
        );


        hierarchyMonitor.update();

    }


    activityLed.update();


    yield();

}