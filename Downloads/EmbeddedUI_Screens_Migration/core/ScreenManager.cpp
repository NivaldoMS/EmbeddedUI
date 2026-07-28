#include "ScreenManager.h"

#include "../drivers/display/DisplayDriver.h"


namespace EmbeddedUI
{


ScreenManager::ScreenManager()
:
_current(nullptr)
{

}


void ScreenManager::begin()
{

    if(_current)
    {

        _current->begin();

    }

}


void ScreenManager::show(
    Screen& screen
)
{

    if(_current == &screen)
    {

        return;

    }


    if(_current)
    {

        _current->end();

    }


    _current =
        &screen;


    _current->begin();

}


void ScreenManager::clear()
{

    if(_current)
    {

        _current->end();

    }


    _current =
        nullptr;

}


Screen* ScreenManager::current() const
{

    return _current;

}


void ScreenManager::update()
{

    if(!_current)
    {

        return;

    }


    _current->update();

}


Result ScreenManager::handleEvent(
    const Event& event
)
{

    if(!_current)
    {

        return Result::IGNORED;

    }


    return
        _current->handleEvent(
            event
        );

}


void ScreenManager::render(
    DisplayDriver& display
)
{

    if(!_current)
    {

        return;

    }


    _current->render(
        display
    );

}


}
