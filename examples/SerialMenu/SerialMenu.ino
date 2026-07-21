#include <Arduino.h>

#include <EmbeddedUI.h>


using namespace EmbeddedUI;


/*
 * Os quatro botões são ligados entre
 * os pinos abaixo e o GND.
 *
 * 2 = CW
 * 3 = CCW
 * 4 = Enter
 * 5 = Back
 */
Buttons buttons(
    2,
    3,
    4,
    5
);



InputManager input;



/*
 * Display lógico de 128x128.
 *
 * Toda a saída será enviada para Serial.
 */
SerialDisplay display(
    Serial,
    128,
    128
);



Theme theme;



/*
 * O SerialDisplay utiliza somente as dimensões
 * da fonte. O ponteiro pode ser nulo.
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



Node saveAction(
    "Save",
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
            .action(saveAction)
        .end()

        .folder(systemFolder)
            .action(resetAction)
        .end();

}



void setup()
{

    Serial.begin(
        115200
    );



    /*
     * Em placas com USB serial nativo,
     * aguarda brevemente a conexão.
     */
    const uint32_t start =
        millis();



    while(
        !Serial &&
        millis() - start < 2000
    )
    {

    }



    configureValues();



    buildMenu();



    menuScreen.setMenu(
        menu
    );



    input.attach(
        buttons
    );



    engine.begin(
        input,
        renderer
    );



    engine.screens().show(
        menuScreen
    );



    Serial.println();
    Serial.println(
        F("Controles:")
    );

    Serial.println(
        F("Botao 1: CW")
    );

    Serial.println(
        F("Botao 2: CCW")
    );

    Serial.println(
        F("Botao 3: Enter")
    );

    Serial.println(
        F("Botao 4: Back")
    );

}



void loop()
{

    engine.update();



    /*
     * Evita imprimir milhares de quadros
     * por segundo no Monitor Serial.
     */
    delay(
        100
    );

}