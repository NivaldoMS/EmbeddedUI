#ifndef EMBEDDED_UI_WEB_SOCKET_INPUT_H
#define EMBEDDED_UI_WEB_SOCKET_INPUT_H


#include <Arduino.h>

#include <EmbeddedUI.h>


using namespace EmbeddedUI;


class WebSocketInput :
    public InputDevice
{

public:


    WebSocketInput();


    void begin() override;


    void update() override;


    bool available() const override;


    InputEvent read() override;


    bool command(
        const char* command
    );


private:


    static constexpr uint8_t EVENT_CAPACITY =
        8;


    static bool equalsIgnoreCase(
        const char* left,
        const char* right
    );


    bool enqueue(
        const InputEvent& event
    );


    void clear();


    InputEvent _events[
        EVENT_CAPACITY
    ];


    uint8_t _head;


    uint8_t _tail;


    uint8_t _count;


};


#endif