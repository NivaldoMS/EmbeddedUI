#include "InputManager.h"


namespace EmbeddedUI
{


UIInputManager::UIInputManager(
    EventQueue& queue
)
:
encoder(nullptr),
eventQueue(queue),
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

            eventQueue.push(
                UIEvent(
                    UIEventType::ENCODER_CW,
                    input.timestamp
                )
            );

        break;



        case UIInputEventType::ROTATE_CCW:

            eventQueue.push(
                UIEvent(
                    UIEventType::ENCODER_CCW,
                    input.timestamp
                )
            );

        break;



        case UIInputEventType::BUTTON_DOWN:

            eventQueue.push(
                UIEvent(
                    UIEventType::BUTTON_ENTER,
                    input.timestamp
                )
            );

        break;



        default:

        break;

    }

}



void UIInputManager::setLongPressEvent(
    UIEventType event
)
{
    longPressEvent = event;
}


}