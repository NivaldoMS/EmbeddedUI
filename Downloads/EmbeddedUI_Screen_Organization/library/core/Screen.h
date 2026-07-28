#ifndef EMBEDDED_UI_SCREEN_H
#define EMBEDDED_UI_SCREEN_H


#include "Event.h"
#include "Types.h"


namespace EmbeddedUI
{


class DisplayDriver;


/**
 * @brief Classe base para telas independentes da interface.
 */
class Screen
{

public:


    Screen();


    virtual ~Screen();


    /**
     * @brief Chamado quando a tela se torna ativa.
     */
    virtual void begin();


    /**
     * @brief Chamado antes da tela deixar de ser ativa.
     */
    virtual void end();


    /**
     * @brief Atualiza a lógica interna da tela.
     */
    virtual void update();


    /**
     * @brief Processa um evento recebido.
     */
    virtual Result handleEvent(
        const Event& event
    );


    /**
     * @brief Desenha a tela diretamente no display.
     */
    virtual void render(
        DisplayDriver& display
    ) = 0;

};


}


#endif
