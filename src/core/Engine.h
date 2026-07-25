#ifndef EMBEDDED_UI_ENGINE_H
#define EMBEDDED_UI_ENGINE_H


#include "ScreenManager.h"

#include "../input/InputManager.h"


namespace EmbeddedUI
{


class Render;


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
        Render& render
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
    void setRender(
        Render& render
    );



    /**
     * @brief Retorna o gerenciador de entrada.
     */
    InputManager* input() const;



    /**
     * @brief Retorna o renderizador.
     */
    Render* render() const;



private:


    ScreenManager _screenManager;


    Render* _render;


    InputManager* _input;


};


}


#endif