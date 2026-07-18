#include "Navigation.h"


namespace EmbeddedUI
{


Navigation::Navigation(
    Menu* menu
)
:
_menu(menu)
{

}



void Navigation::next()
{
    if(!_menu)
        return;


    Node* current =
        _menu->current();


    if(current &&
       current->nextSibling())
    {
        _menu->setCurrent(
            current->nextSibling()
        );
    }
}



void Navigation::previous()
{
    if(!_menu)
        return;


    Node* current =
        _menu->current();


    if(current &&
       current->previousSibling())
    {
        _menu->setCurrent(
            current->previousSibling()
        );
    }
}



bool Navigation::enter()
{
    if(!_menu)
        return false;


    Node* current =
        _menu->current();


    if(current &&
       current->firstChild())
    {
        _menu->setCurrent(
            current->firstChild()
        );

        return true;
    }


    return false;
}



bool Navigation::back()
{
    if(!_menu)
        return false;


    Node* current =
        _menu->current();


    if(current &&
       current->parent())
    {
        _menu->setCurrent(
            current->parent()
        );

        return true;
    }


    return false;
}

void Navigation::handleEvent(
    const UIEvent& event
)
{

    switch(event.type)
    {


        case UIEventType::ENCODER_CW:

            next();

        break;



        case UIEventType::ENCODER_CCW:

            previous();

        break;



        case UIEventType::BUTTON_ENTER:

            enter();

        break;



        case UIEventType::BUTTON_BACK:

            back();

        break;



        default:

        break;

    }

}

}