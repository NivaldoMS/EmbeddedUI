#ifndef EMBEDDED_UI_THEME_H
#define EMBEDDED_UI_THEME_H


#include <Arduino.h>

#include "../render/Bitmap.h"


namespace EmbeddedUI
{


/**
 * @brief Configuração visual da interface.
 */
struct Theme
{

    /*
     * Dimensões gerais.
     */

    uint8_t marginLeft;


    uint8_t marginTop;


    uint8_t lineHeight;



    /*
     * Menu.
     */

    uint8_t selectedIndicatorWidth;


    uint8_t valueWidth;



    /*
     * Cores ou modos de desenho.
     *
     * A interpretação depende do driver.
     */

    uint16_t textColor;


    uint16_t selectedTextColor;


    uint16_t selectedColor;


    uint16_t backgroundColor;



    /*
     * Bitmap opcional de fundo.
     *
     * O Theme não é proprietário do bitmap.
     */

    const Bitmap* background;



    Theme();


};


}


#endif