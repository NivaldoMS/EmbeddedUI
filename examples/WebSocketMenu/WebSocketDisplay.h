#ifndef EMBEDDED_UI_WEB_SOCKET_DISPLAY_H
#define EMBEDDED_UI_WEB_SOCKET_DISPLAY_H


#include <Arduino.h>

#include <WebSocketsServer.h>

#include <EmbeddedUI.h>


using namespace EmbeddedUI;


class WebSocketDisplay :
    public DisplayDriver
{

public:


    explicit WebSocketDisplay(
        WebSocketsServer& webSocket,
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


    void sendCurrentState(
        uint8_t clientNumber
    );


private:


    static constexpr uint8_t MAX_LINES =
        10;


    static constexpr uint8_t LINE_LENGTH =
        48;


    struct DisplayLine
    {

        int16_t x;


        int16_t y;


        bool selected;


        bool editing;


        bool enabled;


        char text[
            LINE_LENGTH
        ];

    };


    static bool isInside(
        int16_t value,
        int16_t start,
        int16_t height,
        bool active
    );


    static void appendText(
        char* destination,
        const char* text,
        size_t capacity
    );


    static void appendEscapedJson(
        String& output,
        const char* text
    );


    DisplayLine* findLine(
        int16_t y
    );


    void applySelectionState();


    void applyEditingState();


    void resetFrame();


    String buildPayload() const;


    void publishIfChanged();


    WebSocketsServer& _webSocket;


    uint16_t _width;


    uint16_t _height;


    uint16_t _drawColor;


    uint8_t _fontWidth;


    uint8_t _fontHeight;


    DisplayLine _lines[
        MAX_LINES
    ];


    uint8_t _lineCount;


    bool _selectionActive;


    int16_t _selectionY;


    int16_t _selectionHeight;


    bool _editingActive;


    int16_t _editingY;


    int16_t _editingHeight;


    String _lastPayload;


};


#endif