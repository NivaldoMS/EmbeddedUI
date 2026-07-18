#ifndef EMBEDDED_UI_EVENT_H
#define EMBEDDED_UI_EVENT_H


#include <Arduino.h>


namespace EmbeddedUI
{


/**
 * @brief Eventos gerados pela interface física.
 */
enum class UIEventType : uint8_t
{
    NONE = 0,

    ENCODER_CW,

    ENCODER_CCW,

    BUTTON_ENTER,

    BUTTON_BACK,

    TIMEOUT
};



/**
 * @brief Evento completo.
 */
struct UIEvent
{
    UIEventType type;

    uint32_t timestamp;


    UIEvent()
        :
        type(UIEventType::NONE),
        timestamp(0)
    {
    }


    UIEvent(UIEventType eventType, uint32_t time)
        :
        type(eventType),
        timestamp(time)
    {
    }
};


}


#endif