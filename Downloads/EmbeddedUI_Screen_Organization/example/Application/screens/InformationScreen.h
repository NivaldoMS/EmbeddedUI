#ifndef APPLICATION_INFORMATION_SCREEN_H
#define APPLICATION_INFORMATION_SCREEN_H

#include <EmbeddedUI.h>

namespace ApplicationScreens
{

class InformationScreen :
    public EmbeddedUI::Screen
{

public:

    InformationScreen(
        EmbeddedUI::ScreenManager& screens,
        EmbeddedUI::Screen& returnScreen
    );

    void setTitle(
        const char* title
    );

    void setLines(
        const char* const* lines,
        uint8_t lineCount
    );

    void begin() override;

    EmbeddedUI::Result handleEvent(
        const EmbeddedUI::Event& event
    ) override;

    void render(
        EmbeddedUI::DisplayDriver& display
    ) override;

private:

    static constexpr uint8_t VisibleLines = 4;

    EmbeddedUI::ScreenManager& _screens;
    EmbeddedUI::Screen& _returnScreen;

    const char* _title;
    const char* const* _lines;

    uint8_t _lineCount;
    uint8_t _firstVisible;

};

}

#endif
