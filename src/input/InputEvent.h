#ifndef EMBEDDED_UI_INPUT_EVENT_H
#define EMBEDDED_UI_INPUT_EVENT_H


#include <Arduino.h>


namespace EmbeddedUI
{


/**
 * @brief Tipos de evento produzidos
 * pelos dispositivos físicos.
 */
enum class InputEventType : uint8_t
{

    NONE = 0,


    ROTATE_CW,


    ROTATE_CCW,


    BUTTON_DOWN,


    BUTTON_UP,


    BUTTON_SHORT_PRESS,


    BUTTON_LONG_PRESS,

    BUTTON_BACK

};



/**
 * @brief Evento de baixo nível produzido
 * por um dispositivo de entrada.
 */
class InputEvent
{

public:


    InputEvent(
        InputEventType type = InputEventType::NONE,
        uint32_t timestamp = 0
    )
    :
    type(type),
    timestamp(timestamp)
    {

    }



    InputEventType type;


    uint32_t timestamp;


};


}


#endif