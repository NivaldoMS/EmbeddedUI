#include "U8g2Display.h"


namespace EmbeddedUI
{


U8g2Display::U8g2Display(
    U8G2& display
)
:
_display(display)
{

}



void U8g2Display::begin()
{

    _display.begin();

}



void U8g2Display::clear()
{

    _display.clearBuffer();

}



void U8g2Display::refresh()
{

    _display.sendBuffer();

}



void U8g2Display::setFont(
    const Font& font
)
{

    if(!font.data())
        return;



    _display.setFont(
        font.data()
    );

}



void U8g2Display::setDrawColor(
    uint16_t color
)
{

    /*
     * U8g2 utiliza:
     *
     * 0 = apagar
     * 1 = desenhar
     * 2 = XOR
     */
    _display.setDrawColor(
        static_cast<uint8_t>(color)
    );

}



void U8g2Display::drawText(
    int16_t x,
    int16_t y,
    const char* text
)
{

    if(!text)
        return;



    _display.drawStr(
        x,
        y,
        text
    );

}



void U8g2Display::drawRect(
    int16_t x,
    int16_t y,
    int16_t width,
    int16_t height
)
{

    if(width <= 0 || height <= 0)
        return;



    _display.drawFrame(
        x,
        y,
        width,
        height
    );

}



void U8g2Display::fillRect(
    int16_t x,
    int16_t y,
    int16_t width,
    int16_t height
)
{

    if(width <= 0 || height <= 0)
        return;



    _display.drawBox(
        x,
        y,
        width,
        height
    );

}



void U8g2Display::drawBitmap(
    int16_t x,
    int16_t y,
    const Bitmap& bitmap
)
{

    if(
        !bitmap.data ||
        bitmap.width == 0 ||
        bitmap.height == 0
    )
    {
        return;
    }



    _display.drawXBMP(
        x,
        y,
        bitmap.width,
        bitmap.height,
        bitmap.data
    );

}



uint16_t U8g2Display::width() const
{

    return
        _display.getDisplayWidth();

}



uint16_t U8g2Display::height() const
{

    return
        _display.getDisplayHeight();

}


}