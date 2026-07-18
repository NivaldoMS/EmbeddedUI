#include <Arduino.h>

#include <U8g2lib.h>

#include <EmbeddedUI.h>


using namespace EmbeddedUI;



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



Node displayFolder(
    "Display",
    NodeType::Folder
);



ValueNode brightnessValue(
    "Brightness",
    ValueType::Integer
);



ValueNode invertValue(
    "Invert",
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
        60.0f
    );



    bassValue.setRange(
        -10.0f,
        10.0f,
        1.0f
    );



    bassValue.setValue(
        0.0f
    );



    brightnessValue.setRange(
        0.0f,
        255.0f,
        5.0f
    );



    brightnessValue.setValue(
        128.0f
    );



    invertValue.setRange(
        0.0f,
        1.0f,
        1.0f
    );



    invertValue.setValue(
        0.0f
    );

}



void buildMenu()
{

    builder
        .folder(audioFolder)
            .value(volumeValue)
            .value(bassValue)
        .end()

        .folder(displayFolder)
            .value(brightnessValue)
            .value(invertValue)
        .end()

        .folder(systemFolder)
            .action(informationAction)
            .action(resetAction)
        .end();

}



void setup()
{

    configureValues();



    buildMenu();



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