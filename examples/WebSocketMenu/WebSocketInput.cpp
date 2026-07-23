#include "WebSocketInput.h"


WebSocketInput::WebSocketInput()
:
_events(),
_head(0),
_tail(0),
_count(0)
{

}


void WebSocketInput::begin()
{

    clear();

}


void WebSocketInput::update()
{

}


bool WebSocketInput::available() const
{

    return
        _count > 0;

}


InputEvent WebSocketInput::read()
{

    if(_count == 0)
    {

        return
            InputEvent();

    }


    const InputEvent event =
        _events[_head];


    _head++;


    if(
        _head >=
        EVENT_CAPACITY
    )
    {

        _head =
            0;

    }


    _count--;


    return event;

}


bool WebSocketInput::command(
    const char* command
)
{

    if(!command)
        return false;


    const uint32_t now =
        millis();


    if(
        equalsIgnoreCase(
            command,
            "CW"
        )
    )
    {

        return enqueue(
            InputEvent(
                InputEventType::ROTATE_CW,
                now
            )
        );

    }


    if(
        equalsIgnoreCase(
            command,
            "CCW"
        )
    )
    {

        return enqueue(
            InputEvent(
                InputEventType::ROTATE_CCW,
                now
            )
        );

    }


    if(
        equalsIgnoreCase(
            command,
            "ENTER"
        )
    )
    {

        return enqueue(
            InputEvent(
                InputEventType::BUTTON_SHORT_PRESS,
                now
            )
        );

    }


    if(
        equalsIgnoreCase(
            command,
            "BACK"
        )
    )
    {

        return enqueue(
            InputEvent(
                InputEventType::BUTTON_BACK,
                now
            )
        );

    }


    return false;

}


bool WebSocketInput::equalsIgnoreCase(
    const char* left,
    const char* right
)
{

    if(
        !left ||
        !right
    )
    {
        return false;
    }


    while(
        *left &&
        *right
    )
    {

        char leftCharacter =
            *left;


        char rightCharacter =
            *right;


        if(
            leftCharacter >= 'a' &&
            leftCharacter <= 'z'
        )
        {

            leftCharacter =
                leftCharacter -
                'a' +
                'A';

        }


        if(
            rightCharacter >= 'a' &&
            rightCharacter <= 'z'
        )
        {

            rightCharacter =
                rightCharacter -
                'a' +
                'A';

        }


        if(
            leftCharacter !=
            rightCharacter
        )
        {
            return false;
        }


        left++;


        right++;

    }


    return
        *left == '\0' &&
        *right == '\0';

}


bool WebSocketInput::enqueue(
    const InputEvent& event
)
{

    if(
        _count >=
        EVENT_CAPACITY
    )
    {
        return false;
    }


    _events[_tail] =
        event;


    _tail++;


    if(
        _tail >=
        EVENT_CAPACITY
    )
    {

        _tail =
            0;

    }


    _count++;


    return true;

}


void WebSocketInput::clear()
{

    _head =
        0;


    _tail =
        0;


    _count =
        0;

}