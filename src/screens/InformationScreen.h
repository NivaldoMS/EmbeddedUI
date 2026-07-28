#ifndef EMBEDDED_UI_INFORMATION_SCREEN_H
#define EMBEDDED_UI_INFORMATION_SCREEN_H


#include "../core/Screen.h"
#include "../core/ScreenManager.h"


namespace EmbeddedUI
{


class DisplayDriver;


class InformationScreen :
    public Screen
{

public:


    InformationScreen(
        ScreenManager& screens,
        Screen& returnScreen
    );


    void setTitle(
        const char* title
    );


    void setLines(
        const char* const* lines,
        uint8_t lineCount
    );


    void begin() override;


    Result handleEvent(
        const Event& event
    ) override;


    void render(
        DisplayDriver& display
    ) override;


private:


    static constexpr uint8_t VisibleLines =
        4;


    ScreenManager& _screens;


    Screen& _returnScreen;


    const char* _title;


    const char* const* _lines;


    uint8_t _lineCount;


    uint8_t _firstVisible;

};


}


#endif
