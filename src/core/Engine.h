#ifndef EMBEDDED_UI_ENGINE_H
#define EMBEDDED_UI_ENGINE_H


#include "ScreenManager.h"

#include "../input/InputManager.h"


namespace EmbeddedUI
{


class Renderer;


/**
 * @brief Núcleo principal da EmbeddedUI.
 *
 * Coordena entrada, telas e renderização.
 */
class Engine
{

public:


    Engine();



    /**
     * @brief Inicializa o motor.
     */
    void begin(
        InputManager& input,
        Renderer& renderer
    );



    /**
     * @brief Executa um ciclo da interface.
     */
    void update();



    /**
     * @brief Renderiza a tela ativa.
     */
    void draw();



    /**
     * @brief Retorna o gerenciador de telas.
     */
    ScreenManager& screens();



    /**
     * @brief Retorna o gerenciador de telas.
     */
    const ScreenManager& screens() const;



    /**
     * @brief Define o gerenciador de entrada.
     */
    void setInput(
        InputManager& input
    );



    /**
     * @brief Define o renderizador.
     */
    void setRenderer(
        Renderer& renderer
    );



    /**
     * @brief Retorna o gerenciador de entrada.
     */
    InputManager* input() const;



    /**
     * @brief Retorna o renderizador.
     */
    Renderer* renderer() const;



private:


    ScreenManager _screenManager;


    Renderer* _renderer;


    InputManager* _input;


};


}


#endif