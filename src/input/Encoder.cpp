#include "Encoder.h"


namespace EmbeddedUI
{


Encoder::Encoder(
    uint8_t pinA,
    uint8_t pinB,
    uint8_t buttonPin
)
:
_pinA(pinA),
_pinB(pinB),
_buttonPin(buttonPin),
_lastA(HIGH),
_buttonState(HIGH),
_lastButtonReading(HIGH),
_lastDebounceTime(0),
_events(),
_head(0),
_tail(0),
_count(0)
{

}



void Encoder::begin()
{

    pinMode(
        _pinA,
        INPUT_PULLUP
    );



    pinMode(
        _pinB,
        INPUT_PULLUP
    );



    pinMode(
        _buttonPin,
        INPUT_PULLUP
    );



    _lastA =
        digitalRead(_pinA);



    _buttonState =
        digitalRead(_buttonPin);



    _lastButtonReading =
        _buttonState;



    _lastDebounceTime =
        millis();



    _head =
        0;



    _tail =
        0;



    _count =
        0;

}



void Encoder::update()
{

    updateRotation();



    updateButton();

}



bool Encoder::available() const
{

    return
        _count > 0;

}



InputEvent Encoder::read()
{

    if(_count == 0)
    {
        return InputEvent();
    }



    InputEvent event =
        _events[_head];



    _head++;



    if(_head >= EVENT_CAPACITY)
    {
        _head = 0;
    }



    _count--;



    return event;

}



bool Encoder::enqueue(
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



void Encoder::updateRotation()
{

    const uint8_t currentA =
        digitalRead(_pinA);



    /*
     * Considera apenas a borda de descida
     * para gerar um evento por passo.
     */
    if(
        _lastA == HIGH &&
        currentA == LOW
    )
    {

        const uint8_t currentB =
            digitalRead(_pinB);



        if(currentB == HIGH)
        {

            enqueue(
                InputEvent(
                    InputEventType::ROTATE_CW,
                    millis()
                )
            );

        }
        else
        {

            enqueue(
                InputEvent(
                    InputEventType::ROTATE_CCW,
                    millis()
                )
            );

        }

    }



    _lastA =
        currentA;

}



void Encoder::updateButton()
{

    const uint8_t reading =
        digitalRead(_buttonPin);



    const uint32_t now =
        millis();



    if(reading != _lastButtonReading)
    {

        _lastDebounceTime =
            now;



        _lastButtonReading =
            reading;

    }



    if(
        now - _lastDebounceTime <
        DEBOUNCE_TIME
    )
    {
        return;
    }



    if(reading == _buttonState)
        return;



    _buttonState =
        reading;



    if(_buttonState == LOW)
    {

        enqueue(
            InputEvent(
                InputEventType::BUTTON_DOWN,
                now
            )
        );

    }
    else
    {

        enqueue(
            InputEvent(
                InputEventType::BUTTON_UP,
                now
            )
        );

    }

}


}