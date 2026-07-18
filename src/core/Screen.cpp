#include "Screen.h"


namespace EmbeddedUI
{


UIScreen::UIScreen()
:
UIComponent(UIComponentType::SCREEN)
{

}



UIScreen::~UIScreen()
{

}



void UIScreen::onEnter()
{

}



void UIScreen::onExit()
{

}



UIResult UIScreen::handleEvent(
    const UIEvent& event
)
{
    return UIComponent::handleEvent(event);
}


}