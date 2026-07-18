#ifndef EMBEDDED_UI_ENGINE_H
#define EMBEDDED_UI_ENGINE_H

#include "core/ScreenManager.h"
#include "render/Renderer.h"
#include "input/InputManager.h"


namespace EmbeddedUI
{


/**
 * @brief Núcleo principal da EmbeddedUI.
 *
 * Coordena:
 * - entrada
 * - telas
 * - renderização
 */
class UIEngine
{

public:


    UIEngine();



    /**
     * @brief Inicializa a interface.
     */
    void begin(
        UIScreen* initialScreen,
        UIDisplayDriver* display,
        UIInputManager input;
    );



    /**
     * @brief Loop principal.
     */
    void update();



    /**
     * @brief Troca tela ativa.
     */
    void show(
        UIScreen* screen
    );



    /**
     * @brief Acesso ao gerenciador de telas.
     */
    UIScreenManager& screens();



private:


    UIScreenManager screenManager;


    UIRenderer renderer;


    UIInputManager input;


};


}


#endif