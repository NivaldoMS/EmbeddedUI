#include "Engine.h"

#include "../render/Renderer.h"


namespace EmbeddedUI
{


Engine::Engine()
:
_screenManager(),
_renderer(nullptr),
_input(nullptr),
_eventQueue()
{

}



void Engine::begin(
    InputManager& input,
    Renderer& renderer
)
{

    setInput(
        input
    );



    setRenderer(
        renderer
    );



    _input->begin();



    _renderer->begin();



    _screenManager.begin();

}



void Engine::update()
{

    if(_input)
    {

        _input->update();



        while(_input->available())
        {

            Event event =
                _input->read();



            _eventQueue.push(
                event
            );

        }

    }



    Event event;



    while(_eventQueue.pop(event))
    {

        _screenManager.handleEvent(
            event
        );

    }



    _screenManager.update();



    draw();

}



void Engine::draw()
{

    if(!_renderer)
        return;



    _screenManager.render(
        *_renderer
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



void Engine::setRenderer(
    Renderer& renderer
)
{

    _renderer =
        &renderer;

}



InputManager* Engine::input() const
{

    return _input;

}



Renderer* Engine::renderer() const
{

    return _renderer;

}


}