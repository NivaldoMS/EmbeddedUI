#include "InputManager.h"


namespace EmbeddedUI
{


UIInputManager::UIInputManager()
:
encoder(nullptr),
pending(),
hasEvent(false),
pressStart(0),
buttonPressed(false),
longPressEvent(UIEventType::NONE)
{

}



void UIInputManager::begin(
    UIEncoder* encoder
)
{

    this->encoder = encoder;


    if(this->encoder)
    {
        this->encoder->begin();
    }

}



void UIInputManager::update()
{

    if(!encoder)
        return;



    encoder->update();



    if(!encoder->available())
        return;



    UIInputEvent input =
        encoder->read();



    switch(input.type)
    {


        case UIInputEventType::ROTATE_CW:

            pending =
                UIEvent(
                    UIEventType::ENCODER_CW,
                    input.timestamp
                );


            hasEvent = true;

        break;



        case UIInputEventType::ROTATE_CCW:

            pending =
                UIEvent(
                    UIEventType::ENCODER_CCW,
                    input.timestamp
                );


            hasEvent = true;

        break;



        case UIInputEventType::BUTTON_DOWN:

            /*
             * Por enquanto:
             *
             * botão curto = ENTER
             *
             * A implementação de
             * short/long press será
             * refinada no próximo ajuste.
             */

            pending =
                UIEvent(
                    UIEventType::BUTTON_ENTER,
                    input.timestamp
                );


            hasEvent = true;


        break;



        default:

        break;

    }


}



bool UIInputManager::available()
{
    return hasEvent;
}



UIEvent UIInputManager::read()
{

    hasEvent = false;


    return pending;

}



void UIInputManager::setLongPressEvent(
    UIEventType event
)
{
    longPressEvent = event;
}


}