#include "InformationScreen.h"

#include "../drivers/display/DisplayDriver.h"


namespace EmbeddedUI
{


InformationScreen::InformationScreen(
    ScreenManager& screens,
    Screen& returnScreen
)
:
_screens(screens),
_returnScreen(returnScreen),
_title("Information"),
_lines(nullptr),
_lineCount(0),
_firstVisible(0)
{

}


void InformationScreen::setTitle(
    const char* title
)
{

    _title =
        title ? title : "";

}


void InformationScreen::setLines(
    const char* const* lines,
    uint8_t lineCount
)
{

    _lines =
        lines;


    _lineCount =
        lineCount;


    _firstVisible =
        0;

}


void InformationScreen::begin()
{

    _firstVisible =
        0;

}


Result InformationScreen::handleEvent(
    const Event& event
)
{

    switch(event.type)
    {

        case EventType::ENCODER_CW:

            if(
                _lineCount > VisibleLines &&
                _firstVisible <
                    _lineCount - VisibleLines
            )
            {

                _firstVisible++;

            }


            return Result::HANDLED;


        case EventType::ENCODER_CCW:

            if(_firstVisible > 0)
            {

                _firstVisible--;

            }


            return Result::HANDLED;


        case EventType::BUTTON_BACK:

            _screens.show(
                _returnScreen
            );


            return Result::HANDLED;


        default:

            return Result::IGNORED;

    }

}


void InformationScreen::render(
    DisplayDriver& display
)
{

    display.beginFrame();


    do
    {

        display.setDrawColor(
            1
        );


        display.drawText(
            3,
            12,
            _title
        );


        display.drawRect(
            0,
            15,
            display.width(),
            1
        );


        for(
            uint8_t line = 0;
            line < VisibleLines;
            line++
        )
        {

            const uint8_t index =
                _firstVisible + line;


            if(
                !_lines ||
                index >= _lineCount
            )
            {

                break;

            }


            display.drawText(
                3,
                27 + line * 12,
                _lines[index]
            );

        }


        if(_firstVisible > 0)
        {

            display.drawText(
                119,
                27,
                "^"
            );

        }


        if(
            _lineCount > VisibleLines &&
            _firstVisible <
                _lineCount - VisibleLines
        )
        {

            display.drawText(
                119,
                63,
                "v"
            );

        }

    }
    while(display.nextFrame());

}


}
