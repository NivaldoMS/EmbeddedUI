#include "MenuApplication.h"


MenuApplication::MenuApplication(
    DisplayDriver& display
)
:
_display(display),
_input(8),
_theme(),
_font(
    nullptr,
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


Node* MenuApplication::selectedNode()
{

    /*
     * O Menu deve manter seu ponteiro current()
     * sincronizado com o Cursor.
     */
    return
        //_menu.current();
        _menuScreen.cursor().current();

}


Node* MenuApplication::editingNode()
{

    /*
     * Necessita que MenuScreen exponha
     * seu InteractionState.
     */
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