#include <Arduino.h>

#include <U8g2lib.h>

#include <EmbeddedUI.h>


using namespace EmbeddedUI;


/*
 * Display SSD1306 128x64 por I2C.
 *
 * Ajuste o construtor conforme o display
 * utilizado no projeto.
 */
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(
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



Encoder encoder(
    2,
    3,
    4
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
            .value(enabledValue)
            .action(saveAction)
        .end();



    menuScreen.setMenu(
        menu
    );



    input.attach(
        encoder
    );



    input.setLongPressEvent(
        EventType::BUTTON_BACK
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