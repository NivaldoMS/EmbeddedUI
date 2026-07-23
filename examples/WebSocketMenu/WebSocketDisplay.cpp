#include "WebSocketDisplay.h"

#include <string.h>


WebSocketDisplay::WebSocketDisplay(
    WebSocketsServer& webSocket,
    uint16_t width,
    uint16_t height
)
:
_webSocket(webSocket),
_width(width),
_height(height),
_drawColor(1),
_fontWidth(0),
_fontHeight(0),
_lines(),
_lineCount(0),
_selectionActive(false),
_selectionY(0),
_selectionHeight(0),
_editingActive(false),
_editingY(0),
_editingHeight(0),
_lastPayload()
{

}


void WebSocketDisplay::begin()
{

    resetFrame();

}


void WebSocketDisplay::beginFrame()
{

    resetFrame();

}


bool WebSocketDisplay::nextFrame()
{

    publishIfChanged();


    return false;

}


void WebSocketDisplay::clear()
{

    resetFrame();

}


void WebSocketDisplay::refresh()
{

    publishIfChanged();

}


void WebSocketDisplay::setFont(
    const Font& font
)
{

    _fontWidth =
        font.width();


    _fontHeight =
        font.height();

}


void WebSocketDisplay::setDrawColor(
    uint16_t color
)
{

    _drawColor =
        color;

}


void WebSocketDisplay::drawText(
    int16_t x,
    int16_t y,
    const char* text
)
{

    if(!text)
        return;


    DisplayLine* line =
        findLine(
            y
        );


    if(!line)
    {

        if(
            _lineCount >=
            MAX_LINES
        )
        {
            return;
        }


        line =
            &_lines[_lineCount];


        line->x =
            x;


        line->y =
            y;


        line->selected =
            isInside(
                y,
                _selectionY,
                _selectionHeight,
                _selectionActive
            );


        line->editing =
            isInside(
                y,
                _editingY,
                _editingHeight,
                _editingActive
            );


        line->enabled =
            true;


        line->text[0] =
            '\0';


        _lineCount++;

    }


    appendText(
        line->text,
        text,
        sizeof(
            line->text
        )
    );


    (void)_drawColor;

}


void WebSocketDisplay::drawRect(
    int16_t x,
    int16_t y,
    int16_t width,
    int16_t height
)
{

    (void)x;


    (void)width;


    _editingActive =
        true;


    _editingY =
        y;


    _editingHeight =
        height;


    applyEditingState();

}


void WebSocketDisplay::fillRect(
    int16_t x,
    int16_t y,
    int16_t width,
    int16_t height
)
{

    (void)x;


    (void)width;


    _selectionActive =
        true;


    _selectionY =
        y;


    _selectionHeight =
        height;


    applySelectionState();

}


void WebSocketDisplay::drawBitmap(
    int16_t x,
    int16_t y,
    const Bitmap& bitmap
)
{

    (void)x;


    (void)y;


    (void)bitmap;

}


uint16_t WebSocketDisplay::width() const
{

    return _width;

}


uint16_t WebSocketDisplay::height() const
{

    return _height;

}


void WebSocketDisplay::sendCurrentState(
    uint8_t clientNumber
)
{

    if(
        _lastPayload.length() == 0
    )
    {
        return;
    }


    _webSocket.sendTXT(
        clientNumber,
        _lastPayload
    );

}


bool WebSocketDisplay::isInside(
    int16_t value,
    int16_t start,
    int16_t height,
    bool active
)
{

    if(!active)
        return false;


    return
        value >= start &&
        value <=
            (
                start +
                height
            );

}


void WebSocketDisplay::appendText(
    char* destination,
    const char* text,
    size_t capacity
)
{

    if(
        !destination ||
        !text ||
        capacity == 0
    )
    {
        return;
    }


    size_t currentLength =
        strlen(
            destination
        );


    if(
        currentLength > 0 &&
        currentLength <
            capacity - 1
    )
    {

        destination[
            currentLength
        ] =
            ' ';


        currentLength++;


        destination[
            currentLength
        ] =
            '\0';

    }


    if(
        currentLength >=
        capacity - 1
    )
    {
        return;
    }


    strncat(
        destination,
        text,
        capacity -
            currentLength -
            1
    );

}


void WebSocketDisplay::appendEscapedJson(
    String& output,
    const char* text
)
{

    if(!text)
        return;


    while(*text)
    {

        const char character =
            *text;


        switch(character)
        {

            case '"':

                output +=
                    F("\\\"");

            break;


            case '\\':

                output +=
                    F("\\\\");

            break;


            case '\n':

                output +=
                    F("\\n");

            break;


            case '\r':

                output +=
                    F("\\r");

            break;


            case '\t':

                output +=
                    F("\\t");

            break;


            default:

                if(
                    static_cast<uint8_t>(
                        character
                    ) >= 32
                )
                {

                    output +=
                        character;

                }

            break;

        }


        text++;

    }

}


WebSocketDisplay::DisplayLine*
WebSocketDisplay::findLine(
    int16_t y
)
{

    for(
        uint8_t i = 0;
        i < _lineCount;
        i++
    )
    {

        if(
            _lines[i].y == y
        )
        {

            return
                &_lines[i];

        }

    }


    return nullptr;

}


void WebSocketDisplay::applySelectionState()
{

    for(
        uint8_t i = 0;
        i < _lineCount;
        i++
    )
    {

        if(
            isInside(
                _lines[i].y,
                _selectionY,
                _selectionHeight,
                _selectionActive
            )
        )
        {

            _lines[i].selected =
                true;

        }

    }

}


void WebSocketDisplay::applyEditingState()
{

    for(
        uint8_t i = 0;
        i < _lineCount;
        i++
    )
    {

        if(
            isInside(
                _lines[i].y,
                _editingY,
                _editingHeight,
                _editingActive
            )
        )
        {

            _lines[i].editing =
                true;

        }

    }

}


void WebSocketDisplay::resetFrame()
{

    _lineCount =
        0;


    _selectionActive =
        false;


    _selectionY =
        0;


    _selectionHeight =
        0;


    _editingActive =
        false;


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


        _lines[i].enabled =
            true;


        _lines[i].text[0] =
            '\0';

    }

}


String WebSocketDisplay::buildPayload() const
{

    String payload;


    payload.reserve(
        512
    );


    payload +=
        F(
            "{\"type\":\"display\","
            "\"width\":"
        );


    payload +=
        _width;


    payload +=
        F(
            ",\"height\":"
        );


    payload +=
        _height;


    payload +=
        F(
            ",\"lines\":["
        );


    for(
        uint8_t i = 0;
        i < _lineCount;
        i++
    )
    {

        if(i > 0)
        {

            payload +=
                ',';

        }


        payload +=
            F(
                "{\"text\":\""
            );


        appendEscapedJson(
            payload,
            _lines[i].text
        );


        payload +=
            F(
                "\",\"selected\":"
            );


        payload +=
            _lines[i].selected
                ? F("true")
                : F("false");


        payload +=
            F(
                ",\"editing\":"
            );


        payload +=
            _lines[i].editing
                ? F("true")
                : F("false");


        payload +=
            F(
                ",\"enabled\":"
            );


        payload +=
            _lines[i].enabled
                ? F("true")
                : F("false");


        payload +=
            '}';

    }


    payload +=
        F(
            "]}"
        );


    return payload;

}


void WebSocketDisplay::publishIfChanged()
{

    const String payload =
        buildPayload();


    if(
        payload ==
        _lastPayload
    )
    {
        return;
    }


    _lastPayload =
        payload;


    _webSocket.broadcastTXT(
        _lastPayload
    );

}