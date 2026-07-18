#include "Font.h"


namespace EmbeddedUI
{


Font::Font(
    const uint8_t* data,
    uint8_t width,
    uint8_t height
)
:
_data(data),
_width(width),
_height(height)
{

}



uint8_t Font::width() const
{
    return _width;
}



uint8_t Font::height() const
{
    return _height;
}



const Glyph Font::glyph(
    char character
) const
{

    Glyph result;


    result.bitmap = nullptr;

    result.width = _width;

    result.height = _height;


    /*
       A busca real do bitmap
       dependerá do formato da fonte.
    */


    return result;

}


}