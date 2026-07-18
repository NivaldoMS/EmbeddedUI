#ifndef EMBEDDED_UI_RENDERER_H
#define EMBEDDED_UI_RENDERER_H


#include "../drivers/DisplayDriver.h"
#include "../menu/MenuScreen.h"

#include "Background.h"

namespace EmbeddedUI
{


/**
 * @brief Renderizador geral da interface.
 */
class UIRenderer
{

public:

    UIBackground background;

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

    void setBackground(
        const UIBitmap* bitmap
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