#include "SerialDisplay.h"

#include <string.h>


namespace EmbeddedUI
{


SerialDisplay::SerialDisplay(
    Stream& serial,
    uint16_t width,
    uint16_t height
)
:
_serial(serial),
_width(width),
_height(height),
_drawColor(1),
_fontWidth(0),
_fontHeight(0),
_frameActive(false),
_bitmapDrawn(false),
_selectionPending(false),
_editingPending(false),
_selectionY(0),
_selectionHeight(0),
_editingY(0),
_editingHeight(0),
_lines(),
_lineCount(0)
{

}



void SerialDisplay::begin()
{

    _serial.println();
    _serial.println(
        F("EmbeddedUI SerialDisplay iniciado")
    );

    _serial.print(
        F("Resolucao logica: ")
    );

    _serial.print(
        _width
    );

    _serial.print(
        'x'
    );

    _serial.println(
        _height
    );

}



void SerialDisplay::beginFrame()
{

    resetFrame();



    _frameActive =
        true;

}



bool SerialDisplay::nextFrame()
{

    printFrame();



    _frameActive =
        false;



    return false;

}



void SerialDisplay::clear()
{

    resetFrame();

}



void SerialDisplay::refresh()
{

    if(_frameActive)
    {

        printFrame();



        _frameActive =
            false;

    }

}



void SerialDisplay::setFont(
    const Font& font
)
{

    _fontWidth =
        font.width();



    _fontHeight =
        font.height();

}



void SerialDisplay::setDrawColor(
    uint16_t color
)
{

    _drawColor =
        color;

}



void SerialDisplay::drawText(
    int16_t x,
    int16_t y,
    const char* text
)
{

    if(!text)
        return;



    TextLine* line =
        findLineByY(
            y
        );



    if(!line)
    {

        if(_lineCount >= MAX_LINES)
            return;



        line =
            &_lines[_lineCount];



        line->x =
            x;



        line->y =
            y;



        line->selected =
            false;



        line->editing =
            false;



        line->text[0] =
            '\0';



        _lineCount++;

    }



    if(
        _selectionPending &&
        y >= _selectionY &&
        y <=
            (
                _selectionY +
                _selectionHeight
            )
    )
    {

        line->selected =
            true;

    }



    if(
        _editingPending &&
        y >= _editingY &&
        y <=
            (
                _editingY +
                _editingHeight
            )
    )
    {

        line->editing =
            true;

    }



    const size_t currentLength =
        strlen(
            line->text
        );



    if(currentLength > 0)
    {

        const size_t remaining =
            LINE_TEXT_SIZE -
            currentLength -
            1;



        if(remaining > 0)
        {

            strncat(
                line->text,
                " ",
                remaining
            );

        }

    }



    const size_t updatedLength =
        strlen(
            line->text
        );



    const size_t remaining =
        LINE_TEXT_SIZE -
        updatedLength -
        1;



    if(remaining > 0)
    {

        strncat(
            line->text,
            text,
            remaining
        );

    }



    (void)_drawColor;

}



void SerialDisplay::drawRect(
    int16_t x,
    int16_t y,
    int16_t width,
    int16_t height
)
{

    (void)x;
    (void)width;



    _editingPending =
        true;



    _editingY =
        y;



    _editingHeight =
        height;



    for(
        uint8_t i = 0;
        i < _lineCount;
        i++
    )
    {

        if(
            _lines[i].y >= y &&
            _lines[i].y <=
                (
                    y +
                    height
                )
        )
        {

            _lines[i].editing =
                true;

        }

    }

}



void SerialDisplay::fillRect(
    int16_t x,
    int16_t y,
    int16_t width,
    int16_t height
)
{

    (void)x;
    (void)width;



    _selectionPending =
        true;



    _selectionY =
        y;



    _selectionHeight =
        height;



    for(
        uint8_t i = 0;
        i < _lineCount;
        i++
    )
    {

        if(
            _lines[i].y >= y &&
            _lines[i].y <=
                (
                    y +
                    height
                )
        )
        {

            _lines[i].selected =
                true;

        }

    }

}



void SerialDisplay::drawBitmap(
    int16_t x,
    int16_t y,
    const Bitmap& bitmap
)
{

    (void)x;
    (void)y;



    if(
        bitmap.data &&
        bitmap.width > 0 &&
        bitmap.height > 0
    )
    {

        _bitmapDrawn =
            true;

    }

}



uint16_t SerialDisplay::width() const
{

    return _width;

}



uint16_t SerialDisplay::height() const
{

    return _height;

}



void SerialDisplay::resetFrame()
{

    _lineCount =
        0;



    _bitmapDrawn =
        false;



    _selectionPending =
        false;



    _editingPending =
        false;



    _selectionY =
        0;



    _selectionHeight =
        0;



    _editingY =
        0;



    _editingHeight =
        0;



    for(
        uint8_t i = 0;
        i < MAX_LINES;
        i++
    )
    {

        _lines[i].x =
            0;



        _lines[i].y =
            0;



        _lines[i].selected =
            false;



        _lines[i].editing =
            false;



        _lines[i].text[0] =
            '\0';

    }

}



void SerialDisplay::printFrame()
{

    _serial.println();
    _serial.println(
        F("========= MENU =========")
    );



    if(_bitmapDrawn)
    {

        _serial.println(
            F("[Background desenhado]")
        );

    }



    if(_lineCount == 0)
    {

        _serial.println(
            F("[Tela vazia]")
        );

    }



    for(
        uint8_t i = 0;
        i < _lineCount;
        i++
    )
    {

        if(_lines[i].selected)
        {

            _serial.print(
                F("> ")
            );

        }
        else
        {

            _serial.print(
                F("  ")
            );

        }



        _serial.print(
            _lines[i].text
        );



        if(_lines[i].editing)
        {

            _serial.print(
                F("  [*]")
            );

        }



        _serial.println();

    }



    _serial.println(
        F("========================")
    );

}



SerialDisplay::TextLine*
SerialDisplay::findLineByY(
    int16_t y
)
{

    for(
        uint8_t i = 0;
        i < _lineCount;
        i++
    )
    {

        if(_lines[i].y == y)
        {

            return
                &_lines[i];

        }

    }



    return nullptr;

}


}