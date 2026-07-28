#include "SplashScreen.h"

#include "../drivers/display/DisplayDriver.h"

#include <Arduino.h>

namespace EmbeddedUI
{

SplashScreen::SplashScreen(
    ScreenManager& screens,
    Screen& nextScreen,
    uint32_t duration
)
:
_screens(screens),
_nextScreen(nextScreen),
_title("EmbeddedUI"),
_message("Inicializando..."),
_duration(duration),
_startedAt(0),
_borderVisible(true)
{

}

void SplashScreen::setTitle(
    const char* title
)
{

    _title =
        title ? title : "";

}

void SplashScreen::setMessage(
    const char* message
)
{

    _message =
        message ? message : "";

}

void SplashScreen::setDuration(
    uint32_t duration
)
{

    _duration = duration;

}

void SplashScreen::setBorderVisible(
    bool visible
)
{

    _borderVisible = visible;

}

void SplashScreen::begin()
{

    _startedAt = millis();

}

void SplashScreen::update()
{

    if(
        millis() - _startedAt >=
        _duration
    )
    {

        _screens.show(
            _nextScreen
        );

    }

}

Result SplashScreen::handleEvent(
    const Event& event
)
{

    (void)event;

    return Result::IGNORED;

}

void SplashScreen::render(
    DisplayDriver& display
)
{

    display.beginFrame();

    do
    {

        display.setDrawColor(1);

        if(_borderVisible)
        {

            display.drawRect(
                3,
                3,
                display.width() - 6,
                display.height() - 6
            );

        }

        display.drawText(
            12,
            27,
            _title
        );

        display.drawText(
            12,
            47,
            _message
        );

    }
    while(display.nextFrame());

}

}
