#ifndef EMBEDDED_UI_THEME_H
#define EMBEDDED_UI_THEME_H


#include <Arduino.h>


namespace EmbeddedUI
{


struct Theme
{

    /*
     * Dimensões gerais
     */

    uint8_t marginLeft;

    uint8_t marginTop;

    uint8_t lineHeight;



    /*
     * Menu
     */

    uint8_t selectedIndicatorWidth;



    /*
     * Cores
     *
     * O tipo será abstrato.
     * O driver decide a conversão.
     */

    uint16_t textColor;

    uint16_t selectedColor;

    uint16_t backgroundColor;



    /*
     * Background
     *
     * Reservado para imagem.
     */

    const uint8_t* background;



    Theme();

};


}


#endif