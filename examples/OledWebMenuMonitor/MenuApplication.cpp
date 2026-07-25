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
_audioFolder(
    "Audio",
    NodeType::Folder
),
_volumeValue(
    "Volume",
    ValueType::Integer
),
_bassValue(
    "Bass",
    ValueType::Integer
),
_enabledValue(
    "Enabled",
    ValueType::Boolean
),
_displayFolder(
    "Display",
    NodeType::Folder
),
_brightnessValue(
    "Brightness",
    ValueType::Integer
),
_contrastValue(
    "Contrast",
    ValueType::Integer
),
_systemFolder(
    "System",
    NodeType::Folder
),
_informationAction(
    "Information",
    NodeType::Action
),
_resetAction(
    "Reset",
    NodeType::Action
),
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


    configureValues();


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


void MenuApplication::configureValues()
{

    _volumeValue.setRange(
        0.0f,
        100.0f,
        1.0f
    );


    _volumeValue.setValue(
        50.0f
    );


    _bassValue.setRange(
        -10.0f,
        10.0f,
        1.0f
    );


    _bassValue.setValue(
        0.0f
    );


    _enabledValue.setRange(
        0.0f,
        1.0f,
        1.0f
    );


    _enabledValue.setValue(
        1.0f
    );


    _brightnessValue.setRange(
        0.0f,
        255.0f,
        5.0f
    );


    _brightnessValue.setValue(
        128.0f
    );


    _contrastValue.setRange(
        0.0f,
        255.0f,
        5.0f
    );


    _contrastValue.setValue(
        180.0f
    );

}


void MenuApplication::buildMenu()
{

    _builder
        .folder(
            _audioFolder
        )
            .value(
                _volumeValue
            )
            .value(
                _bassValue
            )
            .value(
                _enabledValue
            )
        .end()

        .folder(
            _displayFolder
        )
            .value(
                _brightnessValue
            )
            .value(
                _contrastValue
            )
        .end()

        .folder(
            _systemFolder
        )
            .action(
                _informationAction
            )
            .action(
                _resetAction
            )
        .end();

}