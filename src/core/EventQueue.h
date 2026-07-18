#ifndef EMBEDDED_UI_EVENT_QUEUE_H
#define EMBEDDED_UI_EVENT_QUEUE_H

#include "Event.h"


namespace EmbeddedUI
{


class EventQueue
{

public:

    explicit EventQueue(
        uint8_t capacity = 16
    );


    bool push(
        const UIEvent& event
    );


    bool pop(
        UIEvent& event
    );


    bool empty() const;


    void clear();


private:

    UIEvent* _events;

    uint8_t _capacity;

    uint8_t _head;

    uint8_t _tail;

    uint8_t _count;

};


}

#endif