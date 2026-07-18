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



const uint8_t* Font::data() const
{

    return _data;

}



uint8_t Font::width() const
{

    return _width;

}



uint8_t Font::height() const
{

    return _height;

}



Glyph Font::glyph(
    char character
) const
{

    (void)character;



    Glyph result;



    result.bitmap =
        nullptr;



    result.width =
        _width;



    result.height =
        _height;



    /*
     * A obtenção individual do bitmap
     * depende do formato da fonte.
     *
     * Drivers que trabalham diretamente
     * com a fonte nativa não precisam
     * utilizar este método.
     */

    return result;

}



bool Font::valid() const
{

    return
        _data != nullptr;

}


}