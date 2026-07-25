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
_renderer(
    _display,
    _theme,
    _font
),
_engine(),
_menu(),
_menuScreen(),
_audioFolder(),
_volumeValue(),
_balValue(),
_bassValue(),
_midValue(),
_trebleValue(),
_enabledValue(),
_displayFolder(),
_freqValue(),
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
        _renderer
    );


    _engine.screens().show(
        _menuScreen
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


    _theme.marginTop =
        12;


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
                _freqValue,
                "Frequency",
                2,
                "100Hz",
                "120Hz",
                "300Hz",
                "350Hz",
                "500Hz",
                "800Hz"
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
                "Information"
            )

            .action(
                _resetAction,
                "Reset"
            )

        .end();

}