#include "ScreenManager.h"
#include "../render/Renderer.h"

namespace EmbeddedUI
{


UIScreenManager::UIScreenManager()
:
activeScreen(nullptr)
{

}



void UIScreenManager::begin(
    UIScreen* screen
)
{
    activeScreen = screen;


    if(activeScreen)
    {
        activeScreen->begin();
        activeScreen->onEnter();
    }
}



void UIScreenManager::show(
    UIScreen* screen
)
{

    if(activeScreen)
    {
        activeScreen->onExit();
    }


    activeScreen = screen;


    if(activeScreen)
    {
        activeScreen->begin();
        activeScreen->onEnter();
    }

}



UIScreen* UIScreenManager::current()
{
    return activeScreen;
}



void UIScreenManager::update()
{

    if(activeScreen)
    {
        activeScreen->update();
    }

}

void UIScreenManager::render(
    Renderer& renderer
)
{

    if(activeScreen)
    {
        activeScreen->render(
            renderer
        );
    }

}

UIResult UIScreenManager::handleEvent(
    const UIEvent& event
)
{

    if(activeScreen)
    {
        return activeScreen->handleEvent(event);
    }


    return UIResult::NONE;
}


}