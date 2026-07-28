#ifndef EMBEDDED_UI_RESET_SCREEN_H
#define EMBEDDED_UI_RESET_SCREEN_H


#include "../core/Screen.h"
#include "../core/ScreenManager.h"


namespace EmbeddedUI
{


class DisplayDriver;


class ResetScreen :
    public Screen
{

public:


    using TaskCallback =
        void (*)(
            void* context
        );


    ResetScreen(
        ScreenManager& screens,
        Screen& returnScreen,
        uint32_t duration = 2000
    );


    void setTask(
        TaskCallback callback,
        void* context = nullptr
    );


    void setDuration(
        uint32_t duration
    );


    bool finished() const;


    void begin() override;


    void update() override;


    Result handleEvent(
        const Event& event
    ) override;


    void render(
        DisplayDriver& display
    ) override;


private:


    ScreenManager& _screens;


    Screen& _returnScreen;


    TaskCallback _task;


    void* _context;


    uint32_t _duration;


    uint32_t _startedAt;


    bool _finished;

};


}


#endif
