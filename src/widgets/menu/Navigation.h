#ifndef EMBEDDEDUI_NAVIGATION_H
#define EMBEDDEDUI_NAVIGATION_H

#include "Menu.h"
#include "../../core/Event.h"


namespace EmbeddedUI
{


class Navigation
{

public:

    explicit Navigation(
        Menu* menu
    );


    void next();

    void previous();

    bool enter();

    bool back();

    void handleEvent(
        const UIEvent& event
    );

private:

    Menu* _menu;

};


}


#endif