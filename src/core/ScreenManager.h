#ifndef EMBEDDED_UI_SCREEN_MANAGER_H
#define EMBEDDED_UI_SCREEN_MANAGER_H


#include "Screen.h"


namespace EmbeddedUI
{


class Renderer;


/**
 * @brief Gerencia as telas da aplicação.
 *
 * Não cria telas dinamicamente.
 * O usuário fornece as telas existentes.
 */
class UIScreenManager
{

public:


    UIScreenManager();



    /**
     * @brief Define a tela inicial.
     */
    void begin(
        UIScreen* screen
    );



    /**
     * @brief Troca a tela atual.
     */
    void show(
        UIScreen* screen
    );



    /**
     * @brief Retorna tela atual.
     */
    UIScreen* current();



    /**
     * @brief Atualiza a tela ativa.
     */
    void update();



    /**
     * @brief Renderiza a tela ativa.
     */
    void render(
        Renderer& renderer
    );



    /**
     * @brief Envia eventos.
     */
    UIResult handleEvent(
        const UIEvent& event
    );



private:


    UIScreen* activeScreen;


};


}


#endif