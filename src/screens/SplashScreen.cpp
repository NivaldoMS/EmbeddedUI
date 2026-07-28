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
_borderVisible(true),
_renderedOnce(false),
_released(false)
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
    _startedAt =
        0;


    _renderedOnce =
        false;

    _released =
        false;

}

void SplashScreen::update()
{

    if(
        !_renderedOnce ||
        !_released
    )
    {

        return;

    }

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
void SplashScreen::release()
{

    if(_released)
    {

        return;

    }

    _released =
        true;

    _startedAt =
        millis();

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

        display.setDrawColor(
            1
        );


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
    while(
        display.nextFrame()
    );


    if(!_renderedOnce)
    {

        _renderedOnce =
            true;

    }

}

}
