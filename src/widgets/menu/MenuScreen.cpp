#include "MenuScreen.h"

#include "../../render/Renderer.h"


namespace EmbeddedUI
{


MenuScreen::MenuScreen()
:
_menu(nullptr),
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



Menu* MenuScreen::menu() const
{

    return _menu;

}



Result MenuScreen::handleEvent(
    const Event& event
)
{

    if(!_menu)
        return Result::HANDLED;



    _navigation.handleEvent(
        event
    );



    return Result::HANDLED;

}



void MenuScreen::render(
    Renderer& renderer
)
{

    if(!_menu)
        return;



    renderer.render(
        *_menu,
        _cursor,
        _state
    );

}


}