#ifndef EMBEDDED_UI_COMMAND_LED_H
#define EMBEDDED_UI_COMMAND_LED_H


#include <Arduino.h>


class CommandLed
{

public:


    CommandLed(
        uint8_t pin,
        uint16_t blinkTime,
        bool activeLow = true
    );


    void begin();


    void blink();


    void update();


    bool active() const;


private:


    void write(
        bool enabled
    );


    uint8_t _pin;


    uint16_t _blinkTime;


    bool _activeLow;


    bool _active;


    uint32_t _startedAt;


};


#endif