#ifndef EMBEDDED_UI_MENU_SCREEN_H
#define EMBEDDED_UI_MENU_SCREEN_H


#include "../../core/Screen.h"

#include "Menu.h"
#include "Cursor.h"
#include "Navigation.h"
#include "InteractionState.h"


namespace EmbeddedUI
{


class Render;
class DisplayDriver;


/**
 * @brief Tela responsável por exibir e controlar um Menu.
 */
class MenuScreen :
    public Screen
{

public:


    MenuScreen();


    void setMenu(
        Menu& menu
    );


    void setRender(
        Render& render
    );


    Menu* menu() const;


    Result handleEvent(
        const Event& event
    ) override;


    InteractionState& interactionState()
    {

        return _state;

    }


    const InteractionState& interactionState() const
    {

        return _state;

    }


    Cursor& cursor()
    {

        return _cursor;

    }


    const Cursor& cursor() const
    {

        return _cursor;

    }


    void render(
        DisplayDriver& display
    ) override;


private:


    Menu* _menu;


    Render* _render;


    Cursor _cursor;


    InteractionState _state;


    Navigation _navigation;

};


}


#endif
