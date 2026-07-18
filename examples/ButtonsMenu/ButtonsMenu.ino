#include <Arduino.h>

#include <U8g2lib.h>

#include <EmbeddedUI.h>


using namespace EmbeddedUI;


/*
 * Display 128x128 com buffer paginado.
 */
U8G2_SH1107_128X128_1_HW_I2C u8g2(
    U8G2_R0,
    U8X8_PIN_NONE
);


U8g2Display display(
    u8g2
);


Theme theme;


Font font(
    u8g2_font_6x12_tf,
    6,
    12
);


Renderer renderer(
    display,
    theme,
    font
);


/*
 * Botão 1: CW
 * Botão 2: CCW
 * Botão 3: Enter
 * Botão 4: Back
 */
Buttons buttons(
    2,
    3,
    4,
    5
);


InputManager input;


Engine engine;


Menu menu;


MenuScreen menuScreen;


Node settingsFolder(
    "Settings",
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


Node saveAction(
    "Save",
    NodeType::Action
);


Builder builder(
    menu
);


void setup()
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


    builder
        .folder(settingsFolder)
            .value(volumeValue)
            .value(bassValue)
            .value(enabledValue)
            .action(saveAction)
        .end();


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

}


void loop()
{

    engine.update();

}