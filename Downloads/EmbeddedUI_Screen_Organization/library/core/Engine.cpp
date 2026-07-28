#include "Engine.h"

#include "../render/Render.h"
#include "../drivers/display/DisplayDriver.h"


namespace EmbeddedUI
{


Engine::Engine()
:
_screenManager(),
_render(nullptr),
_display(nullptr),
_input(nullptr)
{

}


void Engine::begin(
    InputManager& input,
    Render& render
)
{

    setInput(
        input
    );


    setRender(
        render
    );


    _input->begin();


    /*
     * Nesta etapa de migração, Render ainda configura
     * o display, a fonte, o tema e o layout do menu.
     */
    _render->begin();


    _display =
        &_render->display();


    _screenManager.begin();

}


void Engine::update()
{

    if(_input)
    {

        _input->update();


        while(_input->available())
        {

            const Event event =
                _input->read();


            if(event.type != EventType::NONE)
            {

                _screenManager.handleEvent(
                    event
                );

            }

        }

    }


    _screenManager.update();


    draw();

}


void Engine::draw()
{

    if(!_display)
    {

        return;

    }


    _screenManager.render(
        *_display
    );

}


ScreenManager& Engine::screens()
{

    return _screenManager;

}


const ScreenManager& Engine::screens() const
{

    return _screenManager;

}


void Engine::setInput(
    InputManager& input
)
{

    _input =
        &input;

}


void Engine::setRender(
    Render& render
)
{

    _render =
        &render;


    _display =
        &render.display();

}


InputManager* Engine::input() const
{

    return _input;

}


Render* Engine::render() const
{

    return _render;

}


DisplayDriver* Engine::display() const
{

    return _display;

}


}
