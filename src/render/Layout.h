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


    Layout(
        const Theme& theme
    );



    uint16_t lineY(
        uint8_t line
    ) const;



    int16_t valueX(
        uint16_t displayWidth
    ) const;



    Rect itemRect(
        uint8_t line,
        uint16_t displayWidth
    ) const;



private:


    const Theme& _theme;


};


}


#endif