#ifndef EMBEDDED_UI_NULL_DISPLAY_H
#define EMBEDDED_UI_NULL_DISPLAY_H


#include <Arduino.h>

#include "DisplayDriver.h"


namespace EmbeddedUI
{


class NullDisplay :
    public DisplayDriver
{

public:


    NullDisplay(
        uint16_t width = 128,
        uint16_t height = 64
    )
    :
    _width(width),
    _height(height)
    {

    }


    void begin() override
    {

    }


    void beginFrame() override
    {

    }


    bool nextFrame() override
    {

        return false;

    }


    void clear() override
    {

    }


    void refresh() override
    {

    }


    void setFont(
        const Font& font
    ) override
    {

        (void)font;

    }


    void setDrawColor(
        uint16_t color
    ) override
    {

        (void)color;

    }


    void drawText(
        int16_t x,
        int16_t y,
        const char* text
    ) override
    {

        (void)x;
        (void)y;
        (void)text;

    }


    void drawRect(
        int16_t x,
        int16_t y,
        int16_t width,
        int16_t height
    ) override
    {

        (void)x;
        (void)y;
        (void)width;
        (void)height;

    }


    void fillRect(
        int16_t x,
        int16_t y,
        int16_t width,
        int16_t height
    ) override
    {

        (void)x;
        (void)y;
        (void)width;
        (void)height;

    }


    void drawBitmap(
        int16_t x,
        int16_t y,
        const Bitmap& bitmap
    ) override
    {

        (void)x;
        (void)y;
        (void)bitmap;

    }


    uint16_t width() const override
    {

        return _width;

    }


    uint16_t height() const override
    {

        return _height;

    }


private:


    uint16_t _width;


    uint16_t _height;


};


}


#endif