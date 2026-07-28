#include "ResetScreen.h"

#include "../drivers/display/DisplayDriver.h"

#include <Arduino.h>


namespace EmbeddedUI
{


ResetScreen::ResetScreen(
    ScreenManager& screens,
    Screen& returnScreen,
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

    _task =
        callback;


    _context =
        context;

}


void ResetScreen::setDuration(
    uint32_t duration
)
{

    _duration =
        duration;

}


bool ResetScreen::finished() const
{

    return _finished;

}


void ResetScreen::begin()
{

    _startedAt =
        millis();


    _finished =
        false;


    _renderedOnce =
        false;


    _taskExecuted =
        false;

}


void ResetScreen::update()
{

    /*
     * Aguarda pelo menos uma renderização antes
     * de executar a tarefa de reinicialização.
     */
    if(
        _renderedOnce &&
        !_taskExecuted
    )
    {

        _taskExecuted =
            true;


        if(_task)
        {

            _task(
                _context
            );

        }


        /*
         * O tempo da mensagem final começa após
         * a conclusão da tarefa.
         */
        _startedAt =
            millis();

    }


    if(
        !_finished &&
        _taskExecuted &&
        millis() - _startedAt >= _duration
    )
    {

        _finished =
            true;

    }

}

Result ResetScreen::handleEvent(
    const Event& event
)
{

    if(
        event.type == EventType::BUTTON_BACK &&
        _finished
    )
    {

        _screens.show(
            _returnScreen
        );


        return Result::HANDLED;

    }


    return Result::IGNORED;

}


void ResetScreen::render(
    DisplayDriver& display
)
{

    display.beginFrame();


    do
    {

        display.setDrawColor(
            1
        );


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
    while(
        display.nextFrame()
    );


    /*
     * Informa ao update() que a tela inicial
     * já foi enviada ao display.
     */
    _renderedOnce =
        true;

}

}
