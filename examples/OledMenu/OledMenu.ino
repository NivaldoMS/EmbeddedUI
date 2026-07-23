#include <Arduino.h>

#include <Wire.h>

#include <U8g2lib.h>

#include <EmbeddedUI.h>


using namespace EmbeddedUI;


/*
 * OLED SSD1306 128x64 I2C.
 *
 * Buffer paginado:
 * menor consumo de RAM.
 *
 * NodeMCU:
 * SCL = D1 / GPIO5
 * SDA = D2 / GPIO4
 */
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(
    U8G2_R0,
    U8X8_PIN_NONE
);


/*
 * Driver gráfico.
 */
U8g2Display display(
    u8g2
);


/*
 * Tema visual.
 */
Theme theme;


/*
 * Fonte U8g2.
 */
Font font(
    u8g2_font_6x12_tf,
    6,
    12
);


/*
 * Renderizador.
 */
Renderer renderer(
    display,
    theme,
    font
);


/*
 * Controle por quatro botões:
 *
 * D5 = CW
 * D6 = CCW
 * D7 = ENTER
 * D3 = BACK
 */
Buttons buttons(
    D5,
    D6,
    D7,
    D3
);


/*
 * Entrada da interface.
 */
InputManager input(
    4
);


/*
 * Núcleo da interface.
 */
Engine engine;


/*
 * Menu e tela.
 */
Menu menu;

MenuScreen menuScreen;


/*
 * Estrutura do menu.
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


void configureTheme()
{

    /*
     * A primeira linha é desenhada
     * usando a linha de base em Y = 12.
     */
    theme.marginLeft =
        4;


    theme.marginTop =
        12;


    theme.lineHeight =
        12;


    theme.valueWidth =
        34;


    /*
     * Display monocromático:
     *
     * 0 = apagado
     * 1 = aceso
     */
    theme.backgroundColor =
        0;


    theme.textColor =
        1;


    theme.selectedColor =
        1;


    theme.selectedTextColor =
        0;


    /*
     * Sem bitmap de fundo.
     */
    theme.background =
        nullptr;

}


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
        .folder(
            audioFolder
        )
            .value(
                volumeValue
            )
            .value(
                bassValue
            )
            .value(
                enabledValue
            )
        .end()

        .folder(
            displayFolder
        )
            .value(
                brightnessValue
            )
        .end()

        .folder(
            systemFolder
        )
            .action(
                informationAction
            )
            .action(
                resetAction
            )
        .end();

}


void setup()
{

    Serial.begin(
        115200
    );


    delay(
        200
    );


    /*
     * Define explicitamente os pinos I2C.
     */
    Wire.begin(
        D2,
        D1
    );


    configureTheme();


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


    Serial.println(
        F("EmbeddedUI OLED iniciado.")
    );

}


void loop()
{

    engine.update();


    yield();

}