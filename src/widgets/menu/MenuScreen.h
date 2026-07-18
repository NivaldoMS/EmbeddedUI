#ifndef EMBEDDED_UI_MENU_SCREEN_H
#define EMBEDDED_UI_MENU_SCREEN_H


#include "../core/Screen.h"

#include "Menu.h"
#include "Cursor.h"
#include "Navigation.h"
#include "InteractionState.h"



namespace EmbeddedUI
{


class UIMenuScreen :
    public UIScreen
{

public:


    UIMenuScreen();



    void setMenu(
        Menu& menu
    );



    UIResult handleEvent(
        const UIEvent& event
    ) override;



    void render(
        Renderer& renderer
    ) override;



private:


    Menu* _menu;


    Cursor _cursor;


    InteractionState _state;


    Navigation _navigation;


};


}


#endif