#ifndef EMBEDDED_UI_SCREEN_H
#define EMBEDDED_UI_SCREEN_H


#include "core/Component.h"


namespace EmbeddedUI
{


/**
 * @brief Classe base para todas as telas.
 *
 * Uma tela representa uma área completa
 * da interface do usuário.
 */
class UIScreen : public UIComponent
{

public:


    UIScreen();


    virtual ~UIScreen();


    /**
     * @brief Chamado quando a tela se torna ativa.
     */
    virtual void onEnter();


    /**
     * @brief Chamado antes da tela ser removida.
     */
    virtual void onExit();


    /**
     * @brief Processa eventos.
     */
    virtual UIResult handleEvent(
        const UIEvent& event
    ) override;


};


}


#endif