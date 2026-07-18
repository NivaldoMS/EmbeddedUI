#ifndef EMBEDDED_UI_INPUT_MANAGER_H
#define EMBEDDED_UI_INPUT_MANAGER_H


#include <Arduino.h>

#include "InputDevice.h"
#include "InputEvent.h"

#include "../core/Event.h"
#include "../core/EventQueue.h"


namespace EmbeddedUI
{


class InputManager
{

public:


    explicit InputManager(
        uint8_t capacity = 4
    );



    /**
     * @brief Associa qualquer dispositivo
     * compatível com InputDevice.
     */
    void attach(
        InputDevice& device
    );



    void detach();



    void begin();



    void update();



    bool available() const;



    Event read();



    void setLongPressEvent(
        EventType event
    );



private:


    void processInputEvent(
        const InputEvent& event
    );



    InputDevice* _device;


    EventQueue _events;


    uint32_t _pressStart;


    bool _buttonPressed;


    bool _longPressTriggered;


    EventType _longPressEvent;



    static constexpr uint16_t LONG_PRESS_TIME =
        800;


};


}


#endif