#include "MenuScreen.h"

#include "../../render/Render.h"
#include "../../drivers/display/DisplayDriver.h"


namespace EmbeddedUI
{


MenuScreen::MenuScreen()
:
_menu(nullptr),
_render(nullptr),
_cursor(),
_state(),
_navigation(
    _cursor,
    _state
)
{

}


void MenuScreen::setMenu(
    Menu& menu
)
{

    _menu =
        &menu;


    _state.leaveEdit();


    Node* initial =
        menu.root()->firstChild();


    if(initial)
    {

        _cursor.attach(
            initial
        );

    }
    else
    {

        _cursor.attach(
            menu.root()
        );

    }

}


void MenuScreen::setRender(
    Render& render
)
{

    _render =
        &render;

}


Menu* MenuScreen::menu() const
{

    return _menu;

}


Result MenuScreen::handleEvent(
    const Event& event
)
{

    if(!_menu)
    {

        return Result::IGNORED;

    }


    _navigation.handleEvent(
        event
    );


    return Result::HANDLED;

}


void MenuScreen::render(
    DisplayDriver& display
)
{

    (void)display;


    if(
        !_menu ||
        !_render
    )
    {

        return;

    }


    _render->render(
        *_menu,
        _cursor,
        _state
    );

}


}
