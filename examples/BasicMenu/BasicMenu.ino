#include <Arduino.h>

#include <U8g2lib.h>

#include <EmbeddedUI.h>

#include "MenuBackground128.h"


using namespace EmbeddedUI;


/*
 * Use aqui o construtor correspondente ao seu display 128x128.
 *
 * Exemplo para SH1107 128x128 com buffer paginado:
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


Render render(
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


/*
 * Descritor usado pelo Theme.
 *
 * Os dados permanecem na memória de programa.
 */
const Bitmap menuBackground =
{
    MENU_BACKGROUND_128_DATA,
    128,
    128
};

int ledPin = 13;

void blink()
{
    digitalWrite(ledPin, HIGH);   // Turn LED on
    delay(300);                  // Wait 1 second
    digitalWrite(ledPin, LOW);    // Turn LED off
    delay(300); 

}


void setup()
{

    /*
     * Associa o bitmap ao tema antes
     * de inicializar o Render.
     */
    theme.background =
        &menuBackground;


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
        render
    );


    engine.screens().show(
        menuScreen
    );

    pinMode(ledPin, OUTPUT);

}


void loop()
{

    engine.update();

    blink();

}
