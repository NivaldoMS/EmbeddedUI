#ifndef EMBEDDED_UI_ENGINE_H
#define EMBEDDED_UI_ENGINE_H


#include "ScreenManager.h"

#include "../input/InputManager.h"


namespace EmbeddedUI
{


class Render;
class DisplayDriver;


/**
 * @brief Núcleo principal da EmbeddedUI.
 *
 * Coordena entrada, telas e o display ativo.
 */
class Engine
{

public:


    Engine();


    /**
     * @brief Inicializa o motor mantendo compatibilidade
     * com a inicialização atual do Render do menu.
     */
    void begin(
        InputManager& input,
        Render& render
    );


    void update();


    void draw();


    ScreenManager& screens();


    const ScreenManager& screens() const;


    void setInput(
        InputManager& input
    );


    void setRender(
        Render& render
    );


    InputManager* input() const;


    Render* render() const;


    DisplayDriver* display() const;


private:


    ScreenManager _screenManager;


    Render* _render;


    DisplayDriver* _display;


    InputManager* _input;

};


}


#endif
