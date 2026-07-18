#include "MenuScreen.h"


namespace EmbeddedUI
{


UIMenuScreen::UIMenuScreen()
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



void UIMenuScreen::setMenu(
    Menu& menu
)
{

    _menu = &menu;


    _cursor.attach(
        menu.root()
    );

}



UIResult UIMenuScreen::handleEvent(
    const UIEvent& event
)
{

    _navigation.handleEvent(
        event
    );


    return UIResult::HANDLED;

}



void UIMenuScreen::render(
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