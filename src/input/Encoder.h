#ifndef EMBEDDED_UI_ENCODER_H
#define EMBEDDED_UI_ENCODER_H


#include <Arduino.h>

#include "InputDevice.h"


namespace EmbeddedUI
{


class Encoder :
    public InputDevice
{

public:


    Encoder(
        uint8_t pinA,
        uint8_t pinB,
        uint8_t buttonPin
    );



    void begin() override;



    void update() override;



    bool available() const override;



    InputEvent read() override;



private:


    bool enqueue(
        const InputEvent& event
    );



    void updateRotation();



    void updateButton();



    uint8_t _pinA;


    uint8_t _pinB;


    uint8_t _buttonPin;



    uint8_t _lastA;


    uint8_t _buttonState;


    uint8_t _lastButtonReading;



    uint32_t _lastDebounceTime;



    static constexpr uint16_t DEBOUNCE_TIME =
        40;



    static constexpr uint8_t EVENT_CAPACITY =
        4;



    InputEvent _events[EVENT_CAPACITY];


    uint8_t _head;


    uint8_t _tail;


    uint8_t _count;


};


}


#endif