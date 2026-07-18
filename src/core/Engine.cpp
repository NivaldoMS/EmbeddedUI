#include "Engine.h"

#include "../render/Renderer.h"


namespace EmbeddedUI
{


Engine::Engine()
:
_screenManager(),
_renderer(nullptr),
_input(nullptr)
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