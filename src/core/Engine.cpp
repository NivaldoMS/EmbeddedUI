#include "Engine.h"

#include "../render/Render.h"


namespace EmbeddedUI
{


Engine::Engine()
:
_screenManager(),
_render(nullptr),
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



    _render->begin();



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

    if(!_render)
        return;



    _screenManager.render(
        *_render
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

}



InputManager* Engine::input() const
{

    return _input;

}



Render* Engine::render() const
{

    return _render;

}


}