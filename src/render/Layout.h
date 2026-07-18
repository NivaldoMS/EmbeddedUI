#ifndef EMBEDDED_UI_LAYOUT_H
#define EMBEDDED_UI_LAYOUT_H


#include <Arduino.h>

#include "../theme/Theme.h"


namespace EmbeddedUI
{


struct Rect
{

    int16_t x;


    int16_t y;


    int16_t width;


    int16_t height;


};



class Layout
{

public:


    explicit Layout(
        const Theme& theme
    );



    /**
     * @brief Retorna a linha de base do texto.
     */
    int16_t lineY(
        uint8_t line
    ) const;



    /**
     * @brief Retorna a posição horizontal
     * reservada ao valor.
     */
    int16_t valueX(
        uint16_t displayWidth
    ) const;



    /**
     * @brief Retorna a área completa de um item.
     */
    Rect itemRect(
        uint8_t line,
        uint16_t displayWidth
    ) const;



    /**
     * @brief Retorna a área reservada ao valor.
     */
    Rect valueRect(
        uint8_t line,
        uint16_t displayWidth
    ) const;



private:


    const Theme& _theme;


};


}


#endif