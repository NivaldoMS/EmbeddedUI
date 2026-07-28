#ifndef APPLICATION_RESET_SCREEN_H
#define APPLICATION_RESET_SCREEN_H

#include <EmbeddedUI.h>

namespace ApplicationScreens
{

class ResetScreen :
    public EmbeddedUI::Screen
{

public:

    using TaskCallback =
        void (*)(void* context);

    ResetScreen(
        EmbeddedUI::ScreenManager& screens,
        EmbeddedUI::Screen& returnScreen,
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

    EmbeddedUI::Result handleEvent(
        const EmbeddedUI::Event& event
    ) override;

    void render(
        EmbeddedUI::DisplayDriver& display
    ) override;

private:

    EmbeddedUI::ScreenManager& _screens;
    EmbeddedUI::Screen& _returnScreen;

    TaskCallback _task;
    void* _context;

    uint32_t _duration;
    uint32_t _startedAt;

    bool _finished;
    bool _renderedOnce;
    bool _taskExecuted;

};

}

#endif
