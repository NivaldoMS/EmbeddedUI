#ifndef EMBEDDED_UI_MENU_SCREEN_H
#define EMBEDDED_UI_MENU_SCREEN_H


#include "Screen.h"
#include "Item.h"


namespace EmbeddedUI
{


/**
 * @brief Tela de navegação de menus.
 */
class UIMenuScreen : public UIScreen
{

public:


    UIMenuScreen();


    /**
     * @brief Define o item raiz do menu.
     */
    void setRoot(
        UIItem* item
    );


    /**
     * @brief Retorna item atual.
     */
    UIItem* currentItem();



    /**
     * @brief Item selecionado atualmente.
     */
    UIItem* selectedItem();



    /**
     * @brief Move cursor para cima.
     */
    void moveUp();



    /**
     * @brief Move cursor para baixo.
     */
    void moveDown();



    /**
     * @brief Confirma seleção.
     */
    void enter();



    /**
     * @brief Volta ao menu anterior.
     */
    void back();



    UIResult handleEvent(
        const UIEvent& event
    ) override;



private:


    UIItem* root;


    UIItem* current;


    uint8_t cursor;



    void selectNext();

    void selectPrevious();


};


}


#endif