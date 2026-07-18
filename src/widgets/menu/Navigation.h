#ifndef EMBEDDED_UI_NAVIGATION_H
#define EMBEDDED_UI_NAVIGATION_H

#include "Cursor.h"
#include "InteractionState.h"
#include "../../core/Event.h"


namespace EmbeddedUI
{


class Navigation
{

public:


    Navigation(
        Cursor& cursor,
        InteractionState& state
    );


    void next();

    void previous();


    bool enter();

    bool back();


    void handleEvent(
        const UIEvent& event
    );



private:


    void editNext();

    void editPrevious();

    void confirm();

    void cancel();



    Cursor& _cursor;

    InteractionState& _state;


};


}


#endif