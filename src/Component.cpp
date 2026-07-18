#include "Component.h"


namespace EmbeddedUI
{


UIComponent::UIComponent(
    UIComponentType componentType
)
:
componentType(componentType),
state(UIState::NORMAL),
visible(true),
visibilityCallback(nullptr)
{

}



UIComponent::~UIComponent()
{

}



void UIComponent::begin()
{

}



void UIComponent::update()
{

}



UIResult UIComponent::handleEvent(
    const UIEvent& event
)
{
    return UIResult::NONE;
}



UIComponentType UIComponent::type() const
{
    return componentType;
}



void UIComponent::setVisible(
    bool state
)
{
    visible = state;
}



bool UIComponent::isVisible() const
{

    if(visibilityCallback)
    {
        return visibilityCallback();
    }

    return visible;
}



void UIComponent::setVisibilityCallback(
    UIVisibilityCallback callback
)
{
    visibilityCallback = callback;
}


}