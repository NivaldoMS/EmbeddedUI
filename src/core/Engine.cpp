#include "Engine.h"


namespace EmbeddedUI
{


UIEngine::UIEngine()
:
renderer(nullptr),
input(nullptr)
{

}



void UIEngine::begin(
    UIScreen* initialScreen,
    UIDisplayDriver& display,
    UIInputManager& input
)
{

    this->input =
        &input;



    screenManager.begin(
        initialScreen
    );



    /*
     * O Renderer precisa ser associado
     * externamente.
     *
     * A criação permanece fora da Engine.
     */

}



void UIEngine::update()
{

    /*
     * 1 - Entrada
     */

    if(input)
    {

        input->update();



        while(input->available())
        {

            UIEvent event =
                input->read();



            screenManager.handleEvent(
                event
            );

        }

    }



    /*
     * 2 - Atualização da tela
     */

    screenManager.update();



    /*
     * 3 - Renderização
     */

    draw();

}



void UIEngine::draw()
{

    if(renderer)
    {

        screenManager.render(
            *renderer
        );

    }

}



void UIEngine::show(
    UIScreen* screen
)
{

    screenManager.show(
        screen
    );

}



UIScreenManager& UIEngine::screens()
{
    return screenManager;
}


}