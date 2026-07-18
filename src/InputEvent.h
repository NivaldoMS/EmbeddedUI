#ifndef EMBEDDED_UI_INPUT_EVENT_H
#define EMBEDDED_UI_INPUT_EVENT_H


#include <Arduino.h>


namespace EmbeddedUI
{


/**
 * @brief Eventos gerados pelos dispositivos físicos.
 */
enum class UIInputEventType : uint8_t
{

    NONE = 0,


    ROTATE_CW,


    ROTATE_CCW,


    BUTTON_DOWN,


    BUTTON_UP,


    BUTTON_SHORT_PRESS,


    BUTTON_LONG_PRESS

};




class UIInputEvent
{

public:


    UIInputEvent(
        UIInputEventType type = UIInputEventType::NONE,
        uint32_t timestamp = 0
    )
    :
    type(type),
    timestamp(timestamp)
    {

    }



    UIInputEventType type;


    uint32_t timestamp;


};



}


#endif