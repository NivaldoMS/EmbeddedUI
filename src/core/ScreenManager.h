#ifndef EMBEDDED_UI_SCREEN_MANAGER_H
#define EMBEDDED_UI_SCREEN_MANAGER_H


#include "Screen.h"


namespace EmbeddedUI
{


class Renderer;


/**
 * @brief Gerencia a tela atualmente ativa.
 *
 * O ScreenManager não é proprietário da tela.
 */
class ScreenManager
{

public:


    ScreenManager();



    /**
     * @brief Inicializa o gerenciador.
     */
    void begin();



    /**
     * @brief Define a tela ativa.
     */
    void show(
        Screen& screen
    );



    /**
     * @brief Remove a tela ativa.
     */
    void clear();



    /**
     * @brief Retorna a tela ativa.
     */
    Screen* current() const;



    /**
     * @brief Atualiza a tela ativa.
     */
    void update();



    /**
     * @brief Encaminha um evento à tela ativa.
     */
    Result handleEvent(
        const Event& event
    );



    /**
     * @brief Renderiza a tela ativa.
     */
    void render(
        Renderer& renderer
    );



private:


    Screen* _current;


};


}


#endif