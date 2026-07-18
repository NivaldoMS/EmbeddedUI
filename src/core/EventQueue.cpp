#include "EventQueue.h"


namespace EmbeddedUI
{


EventQueue::EventQueue(
    uint8_t capacity
)
:
_events(nullptr),
_capacity(
    capacity > 0
    ?
    capacity
    :
    1
),
_head(0),
_tail(0),
_count(0)
{

    _events =
        new Event[_capacity];

}



EventQueue::~EventQueue()
{

    delete[] _events;



    _events =
        nullptr;

}



bool EventQueue::push(
    const Event& event
)
{

    if(full())
        return false;



    _events[_tail] =
        event;



    _tail++;



    if(_tail >= _capacity)
    {
        _tail = 0;
    }



    _count++;



    return true;

}



bool EventQueue::pop(
    Event& event
)
{

    if(empty())
        return false;



    event =
        _events[_head];



    _head++;



    if(_head >= _capacity)
    {
        _head = 0;
    }



    _count--;



    return true;

}



bool EventQueue::empty() const
{

    return
        _count == 0;

}



bool EventQueue::full() const
{

    return
        _count >= _capacity;

}



uint8_t EventQueue::count() const
{

    return _count;

}



uint8_t EventQueue::capacity() const
{

    return _capacity;

}



void EventQueue::clear()
{

    _head =
        0;



    _tail =
        0;



    _count =
        0;

}


}