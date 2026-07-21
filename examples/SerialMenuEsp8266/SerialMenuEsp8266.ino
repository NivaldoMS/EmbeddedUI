#include <Arduino.h>

#include <EmbeddedUI.h>

#include <ctype.h>
#include <string.h>


using namespace EmbeddedUI;


/**
 * @brief Dispositivo de entrada controlado
 * por comandos recebidos pela porta serial.
 *
 * Comandos suportados:
 *
 * CW
 * CCW
 * ENTER
 * BACK
 */
class SerialCommandInput :
    public InputDevice
{

public:


    explicit SerialCommandInput(
        Stream& serial
    )
    :
    _serial(serial),
    _buffer(),
    _length(0),
    _pendingEvent()
    {

    }



    void begin() override
    {

        clearBuffer();

    }



    void update() override
    {

        /*
         * Mantém somente um evento pendente.
         *
         * O InputManager consome esse evento antes
         * da próxima chamada de update().
         */
        if(
            _pendingEvent.type !=
            InputEventType::NONE
        )
        {
            return;
        }



        while(_serial.available() > 0)
        {

            const char character =
                static_cast<char>(
                    _serial.read()
                );



            /*
             * Finalização do comando.
             */
            if(
                character == '\n' ||
                character == '\r'
            )
            {

                if(_length > 0)
                {

                    _buffer[_length] =
                        '\0';



                    processCommand();



                    clearBuffer();



                    if(
                        _pendingEvent.type !=
                        InputEventType::NONE
                    )
                    {
                        return;
                    }

                }



                continue;

            }



            /*
             * Ignora espaços no início.
             */
            if(
                _length == 0 &&
                (
                    character == ' ' ||
                    character == '\t'
                )
            )
            {
                continue;
            }



            /*
             * Protege contra estouro do buffer.
             */
            if(
                _length >=
                COMMAND_BUFFER_SIZE - 1
            )
            {

                clearBuffer();

                continue;

            }



            _buffer[_length] =
                character;



            _length++;

        }

    }



    bool available() const override
    {

        return
            _pendingEvent.type !=
            InputEventType::NONE;

    }



    InputEvent read() override
    {

        const InputEvent event =
            _pendingEvent;



        _pendingEvent =
            InputEvent();



        return event;

    }



private:


    static constexpr uint8_t COMMAND_BUFFER_SIZE =
        16;



    void clearBuffer()
    {

        _length =
            0;



        _buffer[0] =
            '\0';

    }



    void normalizeCommand()
    {

        /*
         * Remove espaços no final.
         */
        while(
            _length > 0 &&
            (
                _buffer[_length - 1] == ' ' ||
                _buffer[_length - 1] == '\t'
            )
        )
        {

            _length--;

        }



        _buffer[_length] =
            '\0';



        /*
         * Converte para letras maiúsculas.
         */
        for(
            uint8_t i = 0;
            i < _length;
            i++
        )
        {

            _buffer[i] =
                static_cast<char>(
                    toupper(
                        static_cast<unsigned char>(
                            _buffer[i]
                        )
                    )
                );

        }

    }



    void processCommand()
    {

        normalizeCommand();



        const uint32_t timestamp =
            millis();



        if(
            strcmp(
                _buffer,
                "CW"
            ) == 0
        )
        {

            _pendingEvent =
                InputEvent(
                    InputEventType::ROTATE_CW,
                    timestamp
                );



            printAcceptedCommand(
                "CW"
            );

            return;

        }



        if(
            strcmp(
                _buffer,
                "CCW"
            ) == 0
        )
        {

            _pendingEvent =
                InputEvent(
                    InputEventType::ROTATE_CCW,
                    timestamp
                );



            printAcceptedCommand(
                "CCW"
            );

            return;

        }



        if(
            strcmp(
                _buffer,
                "ENTER"
            ) == 0
        )
        {

            _pendingEvent =
                InputEvent(
                    InputEventType::BUTTON_SHORT_PRESS,
                    timestamp
                );



            printAcceptedCommand(
                "ENTER"
            );

            return;

        }



        if(
            strcmp(
                _buffer,
                "BACK"
            ) == 0
        )
        {

            _pendingEvent =
                InputEvent(
                    InputEventType::BUTTON_BACK,
                    timestamp
                );



            printAcceptedCommand(
                "BACK"
            );

            return;

        }



        _serial.print(
            F("[Comando invalido] ")
        );



        _serial.println(
            _buffer
        );



        _serial.println(
            F("Use: CW, CCW, Enter ou Back")
        );

    }



    void printAcceptedCommand(
        const char* command
    )
    {

        _serial.print(
            F("[Comando] ")
        );



        _serial.println(
            command
        );

    }



    Stream& _serial;


    char _buffer[COMMAND_BUFFER_SIZE];


    uint8_t _length;


    InputEvent _pendingEvent;


};


/*
 * Entrada simulada pelo Monitor Serial.
 */
SerialCommandInput serialInput(
    Serial
);



/*
 * Display lógico de 128x128.
 *
 * Toda a saída produzida pelo Renderer
 * será convertida em texto.
 */
SerialDisplay display(
    Serial,
    128,
    128
);



Theme theme;



/*
 * O SerialDisplay utiliza apenas
 * as dimensões declaradas da fonte.
 */
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



InputManager input(
    4
);



Engine engine;



Menu menu;



MenuScreen menuScreen;



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

}



void buildMenu()
{

    builder
        .folder(audioFolder)
            .value(volumeValue)
            .value(bassValue)
            .value(enabledValue)
        .end()

        .folder(systemFolder)
            .action(informationAction)
            .action(resetAction)
        .end();

}



void printInstructions()
{

    Serial.println();
    Serial.println(
        F("EmbeddedUI - NodeMCU ESP8266")
    );



    Serial.println(
        F("============================")
    );



    Serial.println(
        F("Digite um comando:")
    );



    Serial.println(
        F("CW    - proximo item")
    );



    Serial.println(
        F("CCW   - item anterior")
    );



    Serial.println(
        F("Enter - entrar ou confirmar")
    );



    Serial.println(
        F("Back  - voltar ou cancelar")
    );



    Serial.println(
        F("============================")
    );



    Serial.println(
        F("Configure o Monitor Serial para:")
    );



    Serial.println(
        F("115200 baud e Nova linha")
    );

}



void setup()
{

    Serial.begin(
        115200
    );



    delay(
        500
    );



    configureValues();



    buildMenu();



    menuScreen.setMenu(
        menu
    );



    input.attach(
        serialInput
    );



    engine.begin(
        input,
        renderer
    );



    engine.screens().show(
        menuScreen
    );



    printInstructions();

}



void loop()
{

    engine.update();



    /*
     * Mantém o ESP8266 responsivo para
     * suas tarefas internas.
     */
    yield();



    delay(
        20
    );

}