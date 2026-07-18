#include "ScreenManager.h"

#include "../render/Renderer.h"


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

    _current =
        &screen;



    _current->begin();

}



void ScreenManager::clear()
{

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
        return;



    _current->update();

}



Result ScreenManager::handleEvent(
    const Event& event
)
{

    if(!_current)
        return Result::IGNORED;



    return
        _current->handleEvent(
            event
        );

}



void ScreenManager::render(
    Renderer& renderer
)
{

    if(!_current)
        return;



    _current->render(
        renderer
    );

}


}