#ifndef EMBEDDED_UI_SERIAL_DISPLAY_H
#define EMBEDDED_UI_SERIAL_DISPLAY_H


#include <Arduino.h>

#include "DisplayDriver.h"

#include "../../font/Font.h"


namespace EmbeddedUI
{


/**
 * @brief Driver de teste que envia a saída
 * da interface para o Monitor Serial.
 *
 * Não desenha pixels reais. As chamadas do
 * Renderer são convertidas em texto.
 */
class SerialDisplay :
    public DisplayDriver
{

public:


    explicit SerialDisplay(
        Stream& serial,
        uint16_t width = 128,
        uint16_t height = 128
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


    static constexpr uint8_t MAX_LINES =
        10;



    static constexpr uint8_t LINE_TEXT_SIZE =
        32;



    struct TextLine
    {

        int16_t x;


        int16_t y;


        bool selected;


        bool editing;


        char text[LINE_TEXT_SIZE];

    };



    void resetFrame();



    void printFrame();



    TextLine* findLineByY(
        int16_t y
    );



    Stream& _serial;


    uint16_t _width;


    uint16_t _height;


    uint16_t _drawColor;


    uint8_t _fontWidth;


    uint8_t _fontHeight;


    bool _frameActive;


    bool _bitmapDrawn;


    bool _selectionPending;


    bool _editingPending;


    int16_t _selectionY;


    int16_t _selectionHeight;


    int16_t _editingY;


    int16_t _editingHeight;


    TextLine _lines[MAX_LINES];


    uint8_t _lineCount;


};


}


#endif