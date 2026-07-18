#ifndef EMBEDDED_UI_BUTTONS_H
#define EMBEDDED_UI_BUTTONS_H


#include <Arduino.h>

#include "InputDevice.h"


namespace EmbeddedUI
{


/**
 * @brief Controle de menu usando quatro botões.
 *
 * Botão 1: ROTATE_CW
 * Botão 2: ROTATE_CCW
 * Botão 3: BUTTON_SHORT_PRESS
 * Botão 4: BUTTON_BACK
 */
class Buttons :
    public InputDevice
{

public:


    Buttons(
        uint8_t clockwisePin,
        uint8_t counterClockwisePin,
        uint8_t enterPin,
        uint8_t backPin
    );



    void begin() override;



    void update() override;



    bool available() const override;



    InputEvent read() override;



private:


    struct ButtonState
    {

        uint8_t pin;


        uint8_t stableState;


        uint8_t lastReading;


        uint32_t lastDebounceTime;

    };



    void updateButton(
        ButtonState& button,
        InputEventType eventType
    );



    bool enqueue(
        const InputEvent& event
    );



    ButtonState _clockwise;


    ButtonState _counterClockwise;


    ButtonState _enter;


    ButtonState _back;



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