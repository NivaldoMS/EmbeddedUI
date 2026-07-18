#ifndef EMBEDDED_UI_U8G2_DISPLAY_H
#define EMBEDDED_UI_U8G2_DISPLAY_H


#include "../DisplayDriver.h"


#include <U8g2lib.h>


namespace EmbeddedUI
{


/**
 * @brief Driver de display usando U8g2.
 */
class U8g2Display :
    public UIDisplayDriver
{

public:


    U8g2Display(
        U8G2& display
    );


    void begin() override;


    void clear() override;


    void refresh() override;



    void drawText(
        int16_t x,
        int16_t y,
        const char* text
    ) override;



    void drawRect(
        int16_t x,
        int16_t y,
        int16_t width,
        int16_t height
    ) override;



    void fillRect(
        int16_t x,
        int16_t y,
        int16_t width,
        int16_t height
    ) override;



    uint16_t width() const override;


    uint16_t height() const override;

    void drawBitmap(
        int16_t x,
        int16_t y,
        const UIBitmap& bitmap
    ) override;

private:


    U8G2& display;


};


}


#endif