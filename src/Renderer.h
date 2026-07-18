#ifndef EMBEDDED_UI_RENDERER_H
#define EMBEDDED_UI_RENDERER_H


#include "DisplayDriver.h"
#include "MenuScreen.h"


namespace EmbeddedUI
{


/**
 * @brief Renderizador geral da interface.
 */
class UIRenderer
{

public:


    UIRenderer();



    /**
     * @brief Define display físico.
     */
    void setDisplay(
        UIDisplayDriver* display
    );



    /**
     * @brief Define tela atual.
     */
    void setScreen(
        UIScreen* screen
    );



    /**
     * @brief Desenha interface.
     */
    void draw();



private:


    UIDisplayDriver* display;


    UIScreen* screen;



    void drawMenu(
        UIMenuScreen* menu
    );


};


}


#endif