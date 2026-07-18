#ifndef EMBEDDED_UI_COMPONENT_H
#define EMBEDDED_UI_COMPONENT_H


#include <Arduino.h>

#include "Types.h"
#include "Callback.h"


namespace EmbeddedUI
{


/**
 * @brief Classe base de todos os elementos visuais da biblioteca.
 */
class Component
{

public:


    Component(
        ComponentType componentType = ComponentType::NONE
    );


    virtual ~Component();



    virtual void begin();


    virtual void update();



    virtual Result handleEvent(
        const Event& event
    );



    ComponentType type() const;



    void setVisible(
        bool state
    );



    bool isVisible() const;



    void setVisibilityCallback(
        VisibilityCallback callback
    );


protected:


    ComponentType componentType;


    State state;


    bool visible;


    VisibilityCallback visibilityCallback;


};


}


#endif