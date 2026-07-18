#include "Screen.h"
#include "../render/Renderer.h"

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
    return UIComponent::handleEvent(
        event
    );
}



void UIScreen::render(
    Renderer& renderer
)
{

    /*
     * Tela base não possui desenho.
     *
     * Classes derivadas implementam.
     */

}


}