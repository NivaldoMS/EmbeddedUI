#include "CommandLed.h"


CommandLed::CommandLed(
    uint8_t pin,
    uint16_t blinkTime,
    bool activeLow
)
:
_pin(pin),
_blinkTime(blinkTime),
_activeLow(activeLow),
_active(false),
_startedAt(0)
{

}


void CommandLed::begin()
{

    pinMode(
        _pin,
        OUTPUT
    );


    write(
        false
    );

}


void CommandLed::blink()
{

    write(
        true
    );


    _startedAt =
        millis();


    _active =
        true;

}


void CommandLed::update()
{

    if(!_active)
        return;


    if(
        millis() - _startedAt <
        _blinkTime
    )
    {
        return;
    }


    write(
        false
    );


    _active =
        false;

}


bool CommandLed::active() const
{

    return _active;

}


void CommandLed::write(
    bool enabled
)
{

    const uint8_t level =
        enabled
        ?
        (
            _activeLow
            ?
            LOW
            :
            HIGH
        )
        :
        (
            _activeLow
            ?
            HIGH
            :
            LOW
        );


    digitalWrite(
        _pin,
        level
    );

}