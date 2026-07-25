#ifndef EMBEDDED_UI_COMMAND_LED_H
#define EMBEDDED_UI_COMMAND_LED_H


#include <Arduino.h>


namespace EmbeddedUI
{


class CommandLed
{

public:


    CommandLed(
        uint8_t pin,
        uint16_t duration,
        bool activeLow = true
    );


    void begin();


    void blink();


    void update();


    void stop();


    bool active() const;


private:


    void write(
        bool enabled
    );


    uint8_t _pin;


    uint16_t _duration;


    bool _activeLow;


    bool _active;


    uint32_t _startedAt;


};


}


#endif