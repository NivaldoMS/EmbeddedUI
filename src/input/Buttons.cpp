#include "Buttons.h"


namespace EmbeddedUI
{


Buttons::Buttons(
    uint8_t clockwisePin,
    uint8_t counterClockwisePin,
    uint8_t enterPin,
    uint8_t backPin
)
:
_clockwise{
    clockwisePin,
    HIGH,
    HIGH,
    0
},
_counterClockwise{
    counterClockwisePin,
    HIGH,
    HIGH,
    0
},
_enter{
    enterPin,
    HIGH,
    HIGH,
    0
},
_back{
    backPin,
    HIGH,
    HIGH,
    0
},
_events(),
_head(0),
_tail(0),
_count(0)
{

}



void Buttons::begin()
{

    pinMode(
        _clockwise.pin,
        INPUT_PULLUP
    );



    pinMode(
        _counterClockwise.pin,
        INPUT_PULLUP
    );



    pinMode(
        _enter.pin,
        INPUT_PULLUP
    );



    pinMode(
        _back.pin,
        INPUT_PULLUP
    );



    _clockwise.stableState =
        digitalRead(_clockwise.pin);



    _clockwise.lastReading =
        _clockwise.stableState;



    _counterClockwise.stableState =
        digitalRead(_counterClockwise.pin);



    _counterClockwise.lastReading =
        _counterClockwise.stableState;



    _enter.stableState =
        digitalRead(_enter.pin);



    _enter.lastReading =
        _enter.stableState;



    _back.stableState =
        digitalRead(_back.pin);



    _back.lastReading =
        _back.stableState;



    const uint32_t now =
        millis();



    _clockwise.lastDebounceTime =
        now;



    _counterClockwise.lastDebounceTime =
        now;



    _enter.lastDebounceTime =
        now;



    _back.lastDebounceTime =
        now;



    _head =
        0;



    _tail =
        0;



    _count =
        0;

}



void Buttons::update()
{

    updateButton(
        _clockwise,
        InputEventType::ROTATE_CW
    );



    updateButton(
        _counterClockwise,
        InputEventType::ROTATE_CCW
    );



    updateButton(
        _enter,
        InputEventType::BUTTON_SHORT_PRESS
    );



    updateButton(
        _back,
        InputEventType::BUTTON_BACK
    );

}



bool Buttons::available() const
{

    return
        _count > 0;

}



InputEvent Buttons::read()
{

    if(_count == 0)
    {
        return InputEvent();
    }



    const InputEvent event =
        _events[_head];



    _head++;



    if(_head >= EVENT_CAPACITY)
    {
        _head = 0;
    }



    _count--;



    return event;

}



void Buttons::updateButton(
    ButtonState& button,
    InputEventType eventType
)
{

    const uint8_t reading =
        digitalRead(button.pin);



    const uint32_t now =
        millis();



    if(reading != button.lastReading)
    {

        button.lastReading =
            reading;



        button.lastDebounceTime =
            now;

    }



    if(
        now - button.lastDebounceTime <
        DEBOUNCE_TIME
    )
    {
        return;
    }



    if(reading == button.stableState)
        return;



    button.stableState =
        reading;



    /*
     * INPUT_PULLUP:
     *
     * LOW significa botão pressionado.
     */
    if(button.stableState == LOW)
    {

        enqueue(
            InputEvent(
                eventType,
                now
            )
        );

    }

}



bool Buttons::enqueue(
    const InputEvent& event
)
{

    if(_count >= EVENT_CAPACITY)
        return false;



    _events[_tail] =
        event;



    _tail++;



    if(_tail >= EVENT_CAPACITY)
    {
        _tail = 0;
    }



    _count++;



    return true;

}


}