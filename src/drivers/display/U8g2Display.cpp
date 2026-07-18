#include "U8g2Display.h"



namespace EmbeddedUI
{


U8g2Display::U8g2Display(
    U8G2& display
)
:
display(display)
{

}



void U8g2Display::begin()
{

    display.begin();

}



void U8g2Display::clear()
{

    display.clearBuffer();

}



void U8g2Display::refresh()
{

    display.sendBuffer();

}



void U8g2Display::drawText(
    int16_t x,
    int16_t y,
    const char* text
)
{

    display.drawStr(
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

    display.drawFrame(
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

    display.drawBox(
        x,
        y,
        width,
        height
    );

}

void U8g2Display::drawBitmap(
    int16_t x,
    int16_t y,
    const UIBitmap& bitmap
)
{

    display.drawXBMP(
        x,
        y,
        bitmap.width,
        bitmap.height,
        bitmap.data
    );

}

uint16_t U8g2Display::width() const
{
    return display.getDisplayWidth();
}



uint16_t U8g2Display::height() const
{
    return display.getDisplayHeight();
}


}