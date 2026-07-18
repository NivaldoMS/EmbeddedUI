#ifndef EMBEDDED_UI_U8G2_DISPLAY_H
#define EMBEDDED_UI_U8G2_DISPLAY_H


#include <U8g2lib.h>

#include "DisplayDriver.h"

#include "../../font/Font.h"


namespace EmbeddedUI
{


/**
 * @brief Driver de display baseado na biblioteca U8g2.
 *
 * Compatível com buffers completos e paginados.
 */
class U8g2Display :
    public DisplayDriver
{

public:


    explicit U8g2Display(
        U8G2& display
    );



    void begin() override;



    void beginFrame() override;



    bool nextFrame() override;



    void clear() override;



    void refresh() override;



    void setFont(
        const Font& font
    ) override;



    void setDrawColor(
        uint16_t color
    ) override;



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



    void drawBitmap(
        int16_t x,
        int16_t y,
        const Bitmap& bitmap
    ) override;



    uint16_t width() const override;



    uint16_t height() const override;



private:


    U8G2& _display;


};


}


#endif