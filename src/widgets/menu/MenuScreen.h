#ifndef EMBEDDED_UI_MENU_SCREEN_H
#define EMBEDDED_UI_MENU_SCREEN_H


#include "../../core/Screen.h"

#include "Menu.h"
#include "Cursor.h"
#include "Navigation.h"
#include "InteractionState.h"


namespace EmbeddedUI
{


class Renderer;


/**
 * @brief Tela responsável por exibir e controlar um Menu.
 */
class MenuScreen :
    public Screen
{

public:


    MenuScreen();



    /**
     * @brief Associa um menu à tela.
     */
    void setMenu(
        Menu& menu
    );



    /**
     * @brief Retorna o menu associado.
     */
    Menu* menu() const;



    /**
     * @brief Processa eventos de navegação.
     */
    Result handleEvent(
        const Event& event
    ) override;



    /**
     * @brief Renderiza o menu associado.
     */
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