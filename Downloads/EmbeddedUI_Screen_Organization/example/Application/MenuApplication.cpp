#include "MenuApplication.h"

#include <U8g2lib.h>


MenuApplication::MenuApplication(
    DisplayDriver& display
)
:
_display(display),
_input(8),
_theme(),
_font(
    u8g2_font_6x12_tf,
    6,
    12
),
_render(
    _display,
    _theme,
    _font
),
_engine(),
_menu(),
_menuScreen(),
_splashScreen(
    _engine.screens(),
    _menuScreen,
    2500
),
_informationScreen(
    _engine.screens(),
    _menuScreen
),
_resetScreen(
    _engine.screens(),
    _menuScreen,
    2000
),
_audioFolder(),
_volumeValue(),
_balValue(),
_bassValue(),
_midValue(),
_trebleValue(),
_lowFreqValue(),
_highFreqValue(),
_enabledValue(),
_displayFolder(),
_brightnessValue(),
_contrastValue(),
_systemFolder(),
_informationAction(),
_resetAction(),
_builder(
    _menu
),
_executingNode(nullptr)
{

}


void MenuApplication::begin(
    InputDevice& inputDevice
)
{

    configureTheme();


    buildMenu();


    _menuScreen.setMenu(
        _menu
    );


    _input.attach(
        inputDevice
    );


    _engine.begin(
        _input,
        _render
    );

    _menuScreen.setRender(
        _render
    );

    static const char* informationLines[] =
    {
        "EmbeddedUI",
        "OLED: 128x64",
        "Driver: U8g2",
        "Input: Buttons",
        "WebSocket: ativo",
        "BACK para sair"
    };

    _informationScreen.setTitle(
        "Information"
    );

    _informationScreen.setLines(
        informationLines,
        sizeof(informationLines) /
        sizeof(informationLines[0])
    );

    _resetScreen.setTask(
        performResetTask,
        this
    );

    _splashScreen.setTitle(
        "EmbeddedUI"
    );

    _splashScreen.setMessage(
        "Inicializando..."
    );

    _splashScreen.setBorderVisible(
        true
    );

    _splashScreen.setDuration(
        2500
    );

    _engine.screens().show(
        _splashScreen
    );


}


void MenuApplication::update()
{

    _engine.update();

}


Menu& MenuApplication::menu()
{

    return _menu;

}


const Menu& MenuApplication::menu() const
{

    return _menu;

}


Node* MenuApplication::selectedNode()
{

    return
        _menuScreen
            .cursor()
            .current();

}


Node* MenuApplication::editingNode()
{

    InteractionState& state =
        _menuScreen.interactionState();


    if(!state.editing())
    {

        return nullptr;

    }


    return
        state.valueNode();

}


Node* MenuApplication::executingNode()
{

    return
        _executingNode;

}


void MenuApplication::startExecuting(
    Node* node
)
{

    _executingNode =
        node;

}


void MenuApplication::stopExecuting()
{

    _executingNode =
        nullptr;

}


void MenuApplication::configureTheme()
{

    /*
     * Configuração para OLED 128×64.
     *
     * Com fonte 6×12, cabem aproximadamente
     * cinco linhas visíveis.
     */
    _theme.marginLeft =
        3;



    /*
     * A faixa superior ocupa:
     *
     * y = 0 até y = 15
     *
     * A primeira linha da área azul utiliza
     * baseline em y = 28.
     */
    _theme.marginTop =
        26;


    _theme.lineHeight =
        12;


    _theme.valueWidth =
        36;


    /*
     * Display monocromático.
     */
    _theme.backgroundColor =
        0;


    _theme.textColor =
        1;


    _theme.selectedColor =
        1;


    _theme.selectedTextColor =
        0;


    _theme.background =
        nullptr;

}

void MenuApplication::handleInformation(
    ActionNode& node,
    void* context
)
{
    (void)node;

    MenuApplication* application =
        static_cast<MenuApplication*>(context);

    if(!application)
        return;

    application->_engine.screens().show(
        application->_informationScreen
    );
}



void MenuApplication::handleReset(
    ActionNode& node,
    void* context
)
{
    (void)node;

    MenuApplication* application =
        static_cast<MenuApplication*>(context);

    if(!application)
        return;

    application->_engine.screens().show(
        application->_resetScreen
    );
}

void MenuApplication::performResetTask(
    void* context
)
{
    MenuApplication* application =
        static_cast<MenuApplication*>(context);

    if(!application)
        return;

    // Coloque aqui a restauração real dos valores.
    // Não use ESP.restart(), pois a tela final precisa permanecer visível.

    Serial.println(
        F("[Reset] Configuracoes restauradas")
    );
}



void MenuApplication::handleBrightnessChanged(
    ValueNode& node,
    float value,
    void* context
)
{

    (void)node;



    MenuApplication* application =
        static_cast<MenuApplication*>(
            context
        );



    if(application == nullptr)
    {

        return;

    }



    const uint8_t brightness =
        static_cast<uint8_t>(
            value
        );



    application->_display.setBrightness(
        brightness
    );



    Serial.print(
        F("[Display] Brightness: ")
    );


    Serial.println(
        brightness
    );

}

void MenuApplication::buildMenu()
{

    _builder
        .begin()

        .folder(
            _audioFolder,
            "Audio"
        )

            .integer(
                _volumeValue,
                "Volume",
                0.0f,
                100.0f,
                1.0f,
                50.0f
            )

            .list(
                _lowFreqValue,
                "Low Freq.",
                2,
                "40Hz",
                "60Hz",
                "80Hz",
                "100Hz",
                "120Hz",
                "300Hz",
                "350Hz",
                "400Hz"
            )

            .list(
                _highFreqValue,
                "High Freq.",
                4,
                "500Hz",
                "600Hz",
                "680Hz",
                "800Hz",
                "900Hz",
                "1.2kHz",
                "2kHz",
                "3kHz",
                "4.5kHz",
                "8kHz",
                "10kHz"
            )

            .integer(
                _balValue,
                "Balance",
                -10.0f,
                10.0f,
                1.0f,
                0.0f
            )

            .integer(
                _bassValue,
                "Bass",
                -10.0f,
                10.0f,
                1.0f,
                0.0f
            )

            .integer(
                _midValue,
                "Middle",
                -10.0f,
                10.0f,
                1.0f,
                0.0f
            )

            .integer(
                _trebleValue,
                "Treble",
                -10.0f,
                10.0f,
                1.0f,
                0.0f
            )

            .boolean(
                _enabledValue,
                "Enabled",
                true
            )

        .end()

        .folder(
            _displayFolder,
            "Display"
        )

            .integer(
                _brightnessValue,
                "Brightness",
                0.0f,
                255.0f,
                5.0f,
                128.0f
            )

            .integer(
                _contrastValue,
                "Contrast",
                0.0f,
                255.0f,
                5.0f,
                180.0f
            )

        .end()

        .folder(
            _systemFolder,
            "System"
        )

            .action(
                _informationAction,
                "Information",
                handleInformation,
                this
            )

            .action(
                _resetAction,
                "Reset",
                handleReset,
                this
            )

        .end();

    _brightnessValue.setChangeCallback(
        handleBrightnessChanged,
        this
    );


}