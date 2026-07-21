#ifndef EMBEDDED_UI_NAVIGATION_H
#define EMBEDDED_UI_NAVIGATION_H


#include "../../core/Event.h"

#include "Cursor.h"
#include "InteractionState.h"


namespace EmbeddedUI
{


class Navigation
{

public:


    Navigation(
        Cursor& cursor,
        InteractionState& state
    );



    /**
     * @brief Avança na navegação ou incrementa
     * o valor atualmente em edição.
     */
    void next();



    /**
     * @brief Retrocede na navegação ou decrementa
     * o valor atualmente em edição.
     */
    void previous();



    /**
     * @brief Entra em um submenu, inicia uma edição
     * ou confirma a edição atual.
     */
    bool enter();



    /**
     * @brief Retorna ao nível anterior ou cancela
     * a edição atual.
     */
    bool back();



    /**
     * @brief Converte um evento de entrada
     * em uma ação de navegação.
     */
    void handleEvent(
        const Event& event
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