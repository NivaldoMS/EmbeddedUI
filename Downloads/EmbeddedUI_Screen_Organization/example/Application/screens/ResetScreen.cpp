#include "ResetScreen.h"

#include <Arduino.h>

namespace ApplicationScreens
{

ResetScreen::ResetScreen(
    EmbeddedUI::ScreenManager& screens,
    EmbeddedUI::Screen& returnScreen,
    uint32_t duration
)
:
_screens(screens),
_returnScreen(returnScreen),
_task(nullptr),
_context(nullptr),
_duration(duration),
_startedAt(0),
_finished(false),
_renderedOnce(false),
_taskExecuted(false)
{

}

void ResetScreen::setTask(
    TaskCallback callback,
    void* context
)
{

    _task = callback;
    _context = context;

}

void ResetScreen::setDuration(
    uint32_t duration
)
{

    _duration = duration;

}

bool ResetScreen::finished() const
{

    return _finished;

}

void ResetScreen::begin()
{

    _startedAt = 0;
    _finished = false;
    _renderedOnce = false;
    _taskExecuted = false;

}

void ResetScreen::update()
{

    if(
        _renderedOnce &&
        !_taskExecuted
    )
    {

        _taskExecuted = true;

        if(_task)
        {

            _task(
                _context
            );

        }

        _startedAt = millis();

    }

    if(
        !_finished &&
        _taskExecuted &&
        millis() - _startedAt >= _duration
    )
    {

        _finished = true;

    }

}

EmbeddedUI::Result ResetScreen::handleEvent(
    const EmbeddedUI::Event& event
)
{

    if(
        event.type == EmbeddedUI::EventType::BUTTON_BACK &&
        _finished
    )
    {

        _screens.show(
            _returnScreen
        );

        return EmbeddedUI::Result::HANDLED;

    }

    return EmbeddedUI::Result::IGNORED;

}

void ResetScreen::render(
    EmbeddedUI::DisplayDriver& display
)
{

    display.beginFrame();

    do
    {

        display.setDrawColor(1);

        display.drawRect(
            3,
            3,
            display.width() - 6,
            display.height() - 6
        );

        if(!_finished)
        {

            display.drawText(
                15,
                26,
                "Reinicializando..."
            );

            display.drawText(
                43,
                46,
                "Aguarde"
            );

        }
        else
        {

            display.drawText(
                36,
                25,
                "Finalizado"
            );

            display.drawText(
                18,
                46,
                "BACK para voltar"
            );

        }

    }
    while(display.nextFrame());

    _renderedOnce = true;

}

}
