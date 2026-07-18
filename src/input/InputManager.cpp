#include "InputManager.h"


namespace EmbeddedUI
{


InputManager::InputManager(
    uint8_t capacity
)
:
_encoder(nullptr),
_events(capacity),
_pressStart(0),
_buttonPressed(false),
_longPressTriggered(false),
_longPressEvent(EventType::NONE)
{

}



void InputManager::attach(
    Encoder& encoder
)
{

    _encoder =
        &encoder;

}



void InputManager::detach()
{

    _encoder =
        nullptr;



    _buttonPressed =
        false;



    _longPressTriggered =
        false;



    _pressStart =
        0;

}



void InputManager::begin()
{

    if(_encoder)
    {
        _encoder->begin();
    }

}



void InputManager::update()
{

    if(!_encoder)
        return;



    _encoder->update();



    while(_encoder->available())
    {

        processInputEvent(
            _encoder->read()
        );

    }



    if(
        _buttonPressed &&
        !_longPressTriggered &&
        _longPressEvent != EventType::NONE
    )
    {

        const uint32_t now =
            millis();



        if(
            now - _pressStart >=
            LONG_PRESS_TIME
        )
        {

            _events.push(
                Event(
                    _longPressEvent,
                    now
                )
            );



            _longPressTriggered =
                true;

        }

    }

}



bool InputManager::available() const
{

    return
        !_events.empty();

}



Event InputManager::read()
{

    Event event;



    if(!_events.pop(event))
    {
        return Event(
            EventType::NONE,
            millis()
        );
    }



    return event;

}



void InputManager::setLongPressEvent(
    EventType event
)
{

    _longPressEvent =
        event;

}



void InputManager::processInputEvent(
    const InputEvent& event
)
{

    switch(event.type)
    {

        case InputEventType::ROTATE_CW:

            _events.push(
                Event(
                    EventType::ENCODER_CW,
                    event.timestamp
                )
            );

        break;



        case InputEventType::ROTATE_CCW:

            _events.push(
                Event(
                    EventType::ENCODER_CCW,
                    event.timestamp
                )
            );

        break;



        case InputEventType::BUTTON_DOWN:

            _buttonPressed =
                true;



            _longPressTriggered =
                false;



            _pressStart =
                event.timestamp;

        break;



        case InputEventType::BUTTON_UP:

            if(
                _buttonPressed &&
                !_longPressTriggered
            )
            {

                _events.push(
                    Event(
                        EventType::BUTTON_ENTER,
                        event.timestamp
                    )
                );

            }



            _buttonPressed =
                false;



            _longPressTriggered =
                false;



            _pressStart =
                0;

        break;



        case InputEventType::BUTTON_SHORT_PRESS:

            _events.push(
                Event(
                    EventType::BUTTON_ENTER,
                    event.timestamp
                )
            );

        break;



        case InputEventType::BUTTON_LONG_PRESS:

            if(_longPressEvent != EventType::NONE)
            {

                _events.push(
                    Event(
                        _longPressEvent,
                        event.timestamp
                    )
                );

            }

        break;



        default:

        break;

    }

}


}