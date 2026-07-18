#include "EventQueue.h"


namespace EmbeddedUI
{


EventQueue::EventQueue(
    uint8_t capacity
)
:
_capacity(capacity),
_head(0),
_tail(0),
_count(0)
{
    _events =
        new UIEvent[_capacity];
}



bool EventQueue::push(
    const UIEvent& event
)
{
    if(_count >= _capacity)
        return false;


    _events[_tail] = event;


    _tail++;

    if(_tail >= _capacity)
        _tail = 0;


    _count++;


    return true;
}



bool EventQueue::pop(
    UIEvent& event
)
{
    if(_count == 0)
        return false;


    event =
        _events[_head];


    _head++;

    if(_head >= _capacity)
        _head = 0;


    _count--;


    return true;
}



bool EventQueue::empty() const
{
    return _count == 0;
}



void EventQueue::clear()
{
    _head = 0;

    _tail = 0;

    _count = 0;
}


}