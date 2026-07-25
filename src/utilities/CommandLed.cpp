#include "CommandLed.h"


namespace EmbeddedUI
{


CommandLed::CommandLed(
    uint8_t pin,
    uint16_t duration,
    bool activeLow
)
:
_pin(pin),
_duration(duration),
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


    stop();

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
        _duration
    )
    {
        return;
    }


    stop();

}


void CommandLed::stop()
{

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

    uint8_t level;


    if(_activeLow)
    {

        level =
            enabled
            ?
            LOW
            :
            HIGH;

    }
    else
    {

        level =
            enabled
            ?
            HIGH
            :
            LOW;

    }


    digitalWrite(
        _pin,
        level
    );

}


}