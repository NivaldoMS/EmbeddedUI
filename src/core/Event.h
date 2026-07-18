#ifndef EMBEDDED_UI_EVENT_H
#define EMBEDDED_UI_EVENT_H


#include <Arduino.h>


namespace EmbeddedUI
{


/**
 * @brief Tipos de eventos processados pela interface.
 */
enum class EventType : uint8_t
{

    NONE = 0,


    ENCODER_CW,


    ENCODER_CCW,


    BUTTON_ENTER,


    BUTTON_BACK,


    TIMEOUT

};



/**
 * @brief Evento de alto nível processado
 * pela EmbeddedUI.
 */
struct Event
{

    EventType type;


    uint32_t timestamp;



    Event(
        EventType type = EventType::NONE,
        uint32_t timestamp = 0
    )
    :
    type(type),
    timestamp(timestamp)
    {

    }


};


}


#endif