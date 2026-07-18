#ifndef EMBEDDED_UI_INPUT_DEVICE_H
#define EMBEDDED_UI_INPUT_DEVICE_H


#include "InputEvent.h"


namespace EmbeddedUI
{


/**
 * @brief Interface base para dispositivos de entrada.
 */
class InputDevice
{

public:


    virtual ~InputDevice()
    {

    }



    virtual void begin() = 0;



    virtual void update() = 0;



    virtual bool available() const = 0;



    virtual InputEvent read() = 0;


};


}


#endif