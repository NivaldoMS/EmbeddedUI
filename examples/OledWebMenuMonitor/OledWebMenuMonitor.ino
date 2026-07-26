#include <Arduino.h>

#include <Wire.h>

#include <U8g2lib.h>

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#endif

#include <WebSocketsServer.h>

#include <EmbeddedUI.h>

#include <extensions/websocket/MenuHierarchyMonitor.h>

#include <utilities/CommandLed.h>

#include "AppConfig.h"
#include "WebPage.h"
#include "MenuApplication.h"

#include <string.h>


using namespace EmbeddedUI;


/*
 * OLED SSD1306 128×64.
 *
 * O sufixo _1_ seleciona buffer paginado,
 * reduzindo o consumo de RAM.
 */
U8G2_SSD1306_128X64_NONAME_1_HW_I2C oled(
    U8G2_R0,
    U8X8_PIN_NONE
);


/*
 * Driver EmbeddedUI para U8g2.
 */
U8g2Display display(
    oled
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
 * Aplicação da interface.
 */
MenuApplication application(
    display
);


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
 * Monitor do estado da EmbeddedUI.
 */
MenuHierarchyMonitor hierarchyMonitor(
    webSocket,
    application.menu()
);


/*
 * LED interno para indicar atividade WebSocket.
 */
CommandLed activityLed(
    AppConfig::ACTIVITY_LED_PIN,
    AppConfig::ACTIVITY_LED_DURATION,
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
        F("Monitor web: http://")
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
             * O navegador apenas solicita
             * o estado inicial.
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

void serialpln(const __FlashStringHelper* text)
{
    Serial.println(text);
}

void serialp(const __FlashStringHelper* text)
{
    Serial.println(text);
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

    /*
     * Inicializa explicitamente o I2C:
     *
     * SDA = D2
     * SCL = D1
     */
    Wire.begin(
        AppConfig::I2C_SDA_PIN,
        AppConfig::I2C_SCL_PIN
    );

    oled.begin();
    oled.firstPage();
    do { } while( oled.nextPage() );

    /*
     * application.begin() inicializa
     * o U8g2Display por meio do Render.
     */
    application.begin(
        buttons
    );

    networkReady =
        connectToWiFi();


    if(!networkReady)
    {

        serialpln(F("OLED e menu iniciados sem monitor web."));

        return;

    }


    configureHttpServer();


    webServer.begin();


    webSocket.begin();


    webSocket.onEvent(
        handleWebSocketEvent
    );


    hierarchyMonitor.forcePublish();


    serialpln(F("OLED e monitor web iniciados."));

}


void loop()
{

    /*
     * Processa botões, navegação e
     * renderização no OLED.
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