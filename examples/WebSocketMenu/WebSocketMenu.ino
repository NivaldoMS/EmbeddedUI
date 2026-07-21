#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include <WebSocketsServer.h>

#include <EmbeddedUI.h>

#include "WebPage.h"

#include <string.h>


using namespace EmbeddedUI;


/*
 * Rede Wi-Fi criada pelo NodeMCU.
 */
//static const char* WIFI_SSID = "EmbeddedUI-Test";
//static const char* WIFI_PASSWORD = "embeddedui";

/*
 * Conecta à uma rede Wi-Fi específica.
 */
static const char* WIFI_SSID = "NMS";
static const char* WIFI_PASSWORD = "*1234567*";

/*
 * LED interno do NodeMCU.
 *
 * Normalmente:
 * LOW  = aceso
 * HIGH = apagado
 */
static constexpr uint8_t COMMAND_LED_PIN = LED_BUILTIN;

static constexpr uint16_t COMMAND_LED_TIME = 60;

bool commandLedActive = false;

uint32_t commandLedStart = 0;


/*
 * Servidor HTTP:
 * http://192.168.4.1
 */
ESP8266WebServer webServer(
    80
);


/*
 * Servidor WebSocket:
 * ws://192.168.4.1:81/
 */
WebSocketsServer webSocket(
    81
);


/*
 * Página HTML armazenada na memória flash.
 */

/**
 * @brief Entrada controlada por mensagens WebSocket.
 */
class WebSocketInput :
    public InputDevice
{

public:


    WebSocketInput()
    :
    _events(),
    _head(0),
    _tail(0),
    _count(0)
    {

    }


    void begin() override
    {

        clear();

    }


    void update() override
    {

    }


    bool available() const override
    {

        return
            _count > 0;

    }


    InputEvent read() override
    {

        if(_count == 0)
        {

            return
                InputEvent();

        }


        const InputEvent event =
            _events[_head];


        _head++;


        if(_head >= EVENT_CAPACITY)
        {

            _head =
                0;

        }


        _count--;


        return event;

    }


    bool command(
        const char* command
    )
    {

        if(!command)
            return false;


        const uint32_t now =
            millis();


        if(
            equalsIgnoreCase(
                command,
                "CW"
            )
        )
        {

            return enqueue(
                InputEvent(
                    InputEventType::ROTATE_CW,
                    now
                )
            );

        }


        if(
            equalsIgnoreCase(
                command,
                "CCW"
            )
        )
        {

            return enqueue(
                InputEvent(
                    InputEventType::ROTATE_CCW,
                    now
                )
            );

        }


        if(
            equalsIgnoreCase(
                command,
                "ENTER"
            )
        )
        {

            return enqueue(
                InputEvent(
                    InputEventType::BUTTON_SHORT_PRESS,
                    now
                )
            );

        }


        if(
            equalsIgnoreCase(
                command,
                "BACK"
            )
        )
        {

            return enqueue(
                InputEvent(
                    InputEventType::BUTTON_BACK,
                    now
                )
            );

        }


        return false;

    }


private:


    static constexpr uint8_t EVENT_CAPACITY =
        8;


    static bool equalsIgnoreCase(
        const char* left,
        const char* right
    )
    {

        if(
            !left ||
            !right
        )
        {
            return false;
        }


        while(
            *left &&
            *right
        )
        {

            char leftCharacter =
                *left;


            char rightCharacter =
                *right;


            if(
                leftCharacter >= 'a' &&
                leftCharacter <= 'z'
            )
            {

                leftCharacter =
                    leftCharacter -
                    'a' +
                    'A';

            }


            if(
                rightCharacter >= 'a' &&
                rightCharacter <= 'z'
            )
            {

                rightCharacter =
                    rightCharacter -
                    'a' +
                    'A';

            }


            if(
                leftCharacter !=
                rightCharacter
            )
            {
                return false;
            }


            left++;
            right++;

        }


        return
            *left == '\0' &&
            *right == '\0';

    }


    bool enqueue(
        const InputEvent& event
    )
    {

        if(
            _count >=
            EVENT_CAPACITY
        )
        {
            return false;
        }


        _events[_tail] =
            event;


        _tail++;


        if(
            _tail >=
            EVENT_CAPACITY
        )
        {

            _tail =
                0;

        }


        _count++;


        return true;

    }


    void clear()
    {

        _head =
            0;


        _tail =
            0;


        _count =
            0;

    }


    InputEvent _events[
        EVENT_CAPACITY
    ];


    uint8_t _head;


    uint8_t _tail;


    uint8_t _count;

};


/**
 * @brief Driver que converte as chamadas do Renderer
 * em um estado textual enviado por WebSocket.
 */
class WebSocketDisplay :
    public DisplayDriver
{

public:


    explicit WebSocketDisplay(
        WebSocketsServer& webSocket,
        uint16_t width = 128,
        uint16_t height = 128
    )
    :
    _webSocket(webSocket),
    _width(width),
    _height(height),
    _drawColor(1),
    _fontWidth(0),
    _fontHeight(0),
    _lineCount(0),
    _selectionActive(false),
    _selectionY(0),
    _selectionHeight(0),
    _editingActive(false),
    _editingY(0),
    _editingHeight(0),
    _lastPayload()
    {

    }


    void begin() override
    {

        resetFrame();

    }


    void beginFrame() override
    {

        resetFrame();

    }


    bool nextFrame() override
    {

        publishIfChanged();


        return false;

    }


    void clear() override
    {

        resetFrame();

    }


    void refresh() override
    {

        publishIfChanged();

    }


    void setFont(
        const Font& font
    ) override
    {

        _fontWidth =
            font.width();


        _fontHeight =
            font.height();

    }


    void setDrawColor(
        uint16_t color
    ) override
    {

        _drawColor =
            color;

    }


    void drawText(
        int16_t x,
        int16_t y,
        const char* text
    ) override
    {

        if(!text)
            return;


        DisplayLine* line =
            findLine(
                y
            );


        if(!line)
        {

            if(
                _lineCount >=
                MAX_LINES
            )
            {
                return;
            }


            line =
                &_lines[
                    _lineCount
                ];


            line->x =
                x;


            line->y =
                y;


            line->selected =
                isInside(
                    y,
                    _selectionY,
                    _selectionHeight,
                    _selectionActive
                );


            line->editing =
                isInside(
                    y,
                    _editingY,
                    _editingHeight,
                    _editingActive
                );


            line->enabled =
                true;


            line->text[0] =
                '\0';


            _lineCount++;

        }


        appendText(
            line->text,
            text,
            sizeof(
                line->text
            )
        );


        (void)_drawColor;

    }


    void drawRect(
        int16_t x,
        int16_t y,
        int16_t width,
        int16_t height
    ) override
    {

        (void)x;
        (void)width;


        _editingActive =
            true;


        _editingY =
            y;


        _editingHeight =
            height;


        applyEditingState();

    }


    void fillRect(
        int16_t x,
        int16_t y,
        int16_t width,
        int16_t height
    ) override
    {

        (void)x;
        (void)width;


        _selectionActive =
            true;


        _selectionY =
            y;


        _selectionHeight =
            height;


        applySelectionState();

    }


    void drawBitmap(
        int16_t x,
        int16_t y,
        const Bitmap& bitmap
    ) override
    {

        (void)x;
        (void)y;
        (void)bitmap;

        /*
         * Neste simulador HTML, o bitmap de fundo
         * pode ser representado pelo CSS da página.
         */

    }


    uint16_t width() const override
    {

        return _width;

    }


    uint16_t height() const override
    {

        return _height;

    }


    void sendCurrentState(
        uint8_t clientNumber
    )
    {

        if(
            _lastPayload.length() == 0
        )
        {
            return;
        }


        _webSocket.sendTXT(
            clientNumber,
            _lastPayload
        );

    }


private:


    static constexpr uint8_t MAX_LINES =
        10;


    static constexpr uint8_t LINE_LENGTH =
        48;


    struct DisplayLine
    {

        int16_t x;


        int16_t y;


        bool selected;


        bool editing;


        bool enabled;


        char text[
            LINE_LENGTH
        ];

    };


    static bool isInside(
        int16_t value,
        int16_t start,
        int16_t height,
        bool active
    )
    {

        if(!active)
            return false;


        return
            value >= start &&
            value <=
                (
                    start +
                    height
                );

    }


    static void appendText(
        char* destination,
        const char* text,
        size_t capacity
    )
    {

        if(
            !destination ||
            !text ||
            capacity == 0
        )
        {
            return;
        }


        size_t currentLength =
            strlen(
                destination
            );


        if(
            currentLength > 0 &&
            currentLength <
                capacity - 1
        )
        {

            destination[
                currentLength
            ] =
                ' ';


            currentLength++;


            destination[
                currentLength
            ] =
                '\0';

        }


        if(
            currentLength >=
            capacity - 1
        )
        {
            return;
        }


        strncat(
            destination,
            text,
            capacity -
                currentLength -
                1
        );

    }


    static void appendEscapedJson(
        String& output,
        const char* text
    )
    {

        if(!text)
            return;


        while(*text)
        {

            const char character =
                *text;


            switch(character)
            {

                case '"':

                    output +=
                        F("\\\"");

                break;


                case '\\':

                    output +=
                        F("\\\\");

                break;


                case '\n':

                    output +=
                        F("\\n");

                break;


                case '\r':

                    output +=
                        F("\\r");

                break;


                case '\t':

                    output +=
                        F("\\t");

                break;


                default:

                    if(
                        static_cast<uint8_t>(
                            character
                        ) >= 32
                    )
                    {

                        output +=
                            character;

                    }

                break;

            }


            text++;

        }

    }


    DisplayLine* findLine(
        int16_t y
    )
    {

        for(
            uint8_t i = 0;
            i < _lineCount;
            i++
        )
        {

            if(
                _lines[i].y == y
            )
            {

                return
                    &_lines[i];

            }

        }


        return nullptr;

    }


    void applySelectionState()
    {

        for(
            uint8_t i = 0;
            i < _lineCount;
            i++
        )
        {

            if(
                isInside(
                    _lines[i].y,
                    _selectionY,
                    _selectionHeight,
                    _selectionActive
                )
            )
            {

                _lines[i].selected =
                    true;

            }

        }

    }


    void applyEditingState()
    {

        for(
            uint8_t i = 0;
            i < _lineCount;
            i++
        )
        {

            if(
                isInside(
                    _lines[i].y,
                    _editingY,
                    _editingHeight,
                    _editingActive
                )
            )
            {

                _lines[i].editing =
                    true;

            }

        }

    }


    void resetFrame()
    {

        _lineCount =
            0;


        _selectionActive =
            false;


        _selectionY =
            0;


        _selectionHeight =
            0;


        _editingActive =
            false;


        _editingY =
            0;


        _editingHeight =
            0;


        for(
            uint8_t i = 0;
            i < MAX_LINES;
            i++
        )
        {

            _lines[i].x =
                0;


            _lines[i].y =
                0;


            _lines[i].selected =
                false;


            _lines[i].editing =
                false;


            _lines[i].enabled =
                true;


            _lines[i].text[0] =
                '\0';

        }

    }


    String buildPayload() const
    {

        String payload;


        payload.reserve(
            512
        );


        payload +=
            F(
                "{\"type\":\"display\","
                "\"width\":"
            );


        payload +=
            _width;


        payload +=
            F(
                ",\"height\":"
            );


        payload +=
            _height;


        payload +=
            F(
                ",\"lines\":["
            );


        for(
            uint8_t i = 0;
            i < _lineCount;
            i++
        )
        {

            if(i > 0)
            {

                payload +=
                    ',';

            }


            payload +=
                F(
                    "{\"text\":\""
                );


            appendEscapedJson(
                payload,
                _lines[i].text
            );


            payload +=
                F(
                    "\",\"selected\":"
                );


            payload +=
                _lines[i].selected
                    ? F("true")
                    : F("false");


            payload +=
                F(
                    ",\"editing\":"
                );


            payload +=
                _lines[i].editing
                    ? F("true")
                    : F("false");


            payload +=
                F(
                    ",\"enabled\":"
                );


            payload +=
                _lines[i].enabled
                    ? F("true")
                    : F("false");


            payload +=
                '}';

        }


        payload +=
            F(
                "]}"
            );


        return payload;

    }


    void publishIfChanged()
    {

        const String payload =
            buildPayload();


        if(
            payload ==
            _lastPayload
        )
        {
            return;
        }


        _lastPayload =
            payload;


        _webSocket.broadcastTXT(
            _lastPayload
        );

    }


    WebSocketsServer& _webSocket;


    uint16_t _width;


    uint16_t _height;


    uint16_t _drawColor;


    uint8_t _fontWidth;


    uint8_t _fontHeight;


    DisplayLine _lines[
        MAX_LINES
    ];


    uint8_t _lineCount;


    bool _selectionActive;


    int16_t _selectionY;


    int16_t _selectionHeight;


    bool _editingActive;


    int16_t _editingY;


    int16_t _editingHeight;


    String _lastPayload;

};


/*
 * Objetos da EmbeddedUI.
 */

WebSocketInput webSocketInput;


WebSocketDisplay display(
    webSocket,
    128,
    128
);


InputManager input(
    8
);


Theme theme;


Font font(
    nullptr,
    6,
    12
);


Renderer renderer(
    display,
    theme,
    font
);


Engine engine;


Menu menu;


MenuScreen menuScreen;


/*
 * Nós do menu.
 */

Node audioFolder(
    "Audio",
    NodeType::Folder
);


ValueNode volumeValue(
    "Volume",
    ValueType::Integer
);


ValueNode bassValue(
    "Bass",
    ValueType::Integer
);


ValueNode enabledValue(
    "Enabled",
    ValueType::Boolean
);


Node displayFolder(
    "Display",
    NodeType::Folder
);


ValueNode brightnessValue(
    "Brightness",
    ValueType::Integer
);


Node systemFolder(
    "System",
    NodeType::Folder
);


Node informationAction(
    "Information",
    NodeType::Action
);


Node resetAction(
    "Reset",
    NodeType::Action
);


Builder builder(
    menu
);


void configureValues()
{

    volumeValue.setRange(
        0.0f,
        100.0f,
        1.0f
    );


    volumeValue.setValue(
        50.0f
    );


    bassValue.setRange(
        -10.0f,
        10.0f,
        1.0f
    );


    bassValue.setValue(
        0.0f
    );


    enabledValue.setRange(
        0.0f,
        1.0f,
        1.0f
    );


    enabledValue.setValue(
        1.0f
    );


    brightnessValue.setRange(
        0.0f,
        255.0f,
        5.0f
    );


    brightnessValue.setValue(
        128.0f
    );

}


void buildMenu()
{

    builder
        .folder(audioFolder)
            .value(volumeValue)
            .value(bassValue)
            .value(enabledValue)
        .end()

        .folder(displayFolder)
            .value(brightnessValue)
        .end()

        .folder(systemFolder)
            .action(informationAction)
            .action(resetAction)
        .end();

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


            display.sendCurrentState(
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

            /*
             * Cria uma cópia terminada em zero.
             */
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

                display.sendCurrentState(
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
                blinkCommandLed();
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
                F(
                    " - "
                )
            );


            Serial.println(
                accepted
                    ? F("aceito")
                    : F("ignorado")
            );

        }
        break;


        default:

        break;

    }

}


void configureWebServer()
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

bool connectToWiFi()
{
    WiFi.mode(
        WIFI_STA
    );

    WiFi.begin(
        WIFI_SSID,
        WIFI_PASSWORD
    );

    Serial.println();
    Serial.print(
        F("Conectando à rede ")
    );

    Serial.println(
        WIFI_SSID
    );

    const uint32_t startTime =
        millis();

    const uint32_t timeout =
        20000;

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

void startAccessPoint()
{

    WiFi.mode(
        WIFI_AP
    );


    const bool started =
        WiFi.softAP(
            WIFI_SSID,
            WIFI_PASSWORD
        );


    Serial.println();


    Serial.println(
        F(
            "EmbeddedUI WebSocket"
        )
    );


    Serial.println(
        F(
            "===================="
        )
    );


    Serial.print(
        F(
            "Access Point: "
        )
    );


    Serial.println(
        started
            ? F("iniciado")
            : F("falhou")
    );


    Serial.print(
        F(
            "SSID: "
        )
    );


    Serial.println(
        WIFI_SSID
    );


    Serial.print(
        F(
            "Senha: "
        )
    );


    Serial.println(
        WIFI_PASSWORD
    );


    Serial.print(
        F(
            "Endereco: http://"
        )
    );


    Serial.println(
        WiFi.softAPIP()
    );

}

/**
 * @brief Inicializa o LED indicador.
 */
void beginCommandLed()
{

    pinMode(
        COMMAND_LED_PIN,
        OUTPUT
    );


    digitalWrite(
        COMMAND_LED_PIN,
        HIGH
    );

}


/**
 * @brief Acende rapidamente o LED ao receber
 * um comando válido.
 *
 * Não utiliza delay(), portanto não bloqueia
 * o WebSocket nem o Engine.
 */
void blinkCommandLed()
{

    digitalWrite(
        COMMAND_LED_PIN,
        LOW
    );


    commandLedStart =
        millis();


    commandLedActive =
        true;

}


/**
 * @brief Atualiza o estado temporizado do LED.
 *
 * Deve ser chamada continuamente no loop().
 */
void updateCommandLed()
{

    if(!commandLedActive)
        return;


    if(
        millis() - commandLedStart <
        COMMAND_LED_TIME
    )
    {
        return;
    }


    digitalWrite(
        COMMAND_LED_PIN,
        HIGH
    );


    commandLedActive =
        false;

}



void setup()
{

    Serial.begin(
        115200
    );

    beginCommandLed();

    delay(
        500
    );


    configureValues();


    buildMenu();


    menuScreen.setMenu(
        menu
    );


    input.attach(
        webSocketInput
    );


    engine.begin(
        input,
        renderer
    );


    engine.screens().show(
        menuScreen
    );


    //startAccessPoint();
    if(!connectToWiFi())
    {
        return;
    }


    configureWebServer();


    webServer.begin();


    webSocket.begin();


    webSocket.onEvent(
        handleWebSocketEvent
    );


    Serial.println(
        F(
            "Servidor HTTP iniciado na porta 80."
        )
    );


    Serial.println(
        F(
            "WebSocket iniciado na porta 81."
        )
    );

}


void loop()
{

    webServer.handleClient();


    webSocket.loop();


    engine.update();

    updateCommandLed();

    /*
     * Permite que o ESP8266 execute
     * suas tarefas internas.
     */
    yield();

}