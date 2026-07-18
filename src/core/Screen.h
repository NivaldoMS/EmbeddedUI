#ifndef EMBEDDED_UI_SCREEN_H
#define EMBEDDED_UI_SCREEN_H


#include "Event.h"
#include "Types.h"


namespace EmbeddedUI
{


class Renderer;


/**
 * @brief Classe base para telas da interface.
 */
class Screen
{

public:


    Screen();


    virtual ~Screen();



    /**
     * @brief Inicializa a tela.
     *
     * Chamado quando a tela é exibida
     * pelo ScreenManager.
     */
    virtual void begin();



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
     * @brief Renderiza a tela.
     */
    virtual void render(
        Renderer& renderer
    ) = 0;


};


}


#endif