#ifndef EMBEDDED_UI_FONT_H
#define EMBEDDED_UI_FONT_H


#include <Arduino.h>


namespace EmbeddedUI
{


struct Glyph
{
    const uint8_t* bitmap;

    uint8_t width;

    uint8_t height;
};



class Font
{

public:


    Font(
        const uint8_t* data,
        uint8_t width,
        uint8_t height
    );



    uint8_t width() const;


    uint8_t height() const;



    const Glyph glyph(
        char character
    ) const;



private:


    const uint8_t* _data;


    uint8_t _width;

    uint8_t _height;


};


}


#endif