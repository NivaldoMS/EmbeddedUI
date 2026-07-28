#ifndef EMBEDDED_UI_SPLASH_SCREEN_H
#define EMBEDDED_UI_SPLASH_SCREEN_H

#include "../core/Screen.h"
#include "../core/ScreenManager.h"

namespace EmbeddedUI
{

class SplashScreen :
    public Screen
{

public:

    SplashScreen(
        ScreenManager& screens,
        Screen& nextScreen,
        uint32_t duration = 2000
    );

    void setTitle(
        const char* title
    );

    void setMessage(
        const char* message
    );

    void setDuration(
        uint32_t duration
    );

    void setBorderVisible(
        bool visible
    );

    void begin() override;
    void update() override;

    Result handleEvent(
        const Event& event
    ) override;

    void render(
        DisplayDriver& display
    ) override;

private:

    ScreenManager& _screens;
    Screen& _nextScreen;

    const char* _title;
    const char* _message;

    uint32_t _duration;
    uint32_t _startedAt;

    bool _borderVisible;

};

}

#endif
