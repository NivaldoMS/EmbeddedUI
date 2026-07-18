#include "Component.h"


namespace EmbeddedUI
{


Component::Component(
    ComponentType componentType
)
:
componentType(componentType),
state(State::NORMAL),
visible(true),
visibilityCallback(nullptr)
{

}



Component::~Component()
{

}



void Component::begin()
{

}



void Component::update()
{

}



Result Component::handleEvent(
    const Event&
)
{
    return Result::NONE;
}



ComponentType Component::type() const
{
    return componentType;
}



void Component::setVisible(
    bool state
)
{
    visible = state;
}



bool Component::isVisible() const
{

    if(visibilityCallback)
    {
        return visibilityCallback();
    }


    return visible;

}



void Component::setVisibilityCallback(
    VisibilityCallback callback
)
{
    visibilityCallback = callback;
}


}