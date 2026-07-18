#include "Engine.h"


namespace EmbeddedUI
{


UIEngine::UIEngine()
:
encoder(nullptr)
{

}



void UIEngine::begin(
    UIScreen* initialScreen,
    UIDisplayDriver* display,
    UIEncoder* encoder
)
{

    this->encoder = encoder;


    if(display)
    {
        renderer.setDisplay(display);
    }


    screenManager.begin(
        initialScreen
    );


    renderer.setScreen(
        initialScreen
    );



    if(this->encoder)
    {
        this->encoder->begin();
    }

}



void UIEngine::update()
{

    /*
     * 1 - Ler entradas
     */
    if(encoder)
    {

        encoder->update();



        if(encoder->available())
        {

            UIEvent event =
                encoder->read();



            screenManager.handleEvent(
                event
            );

        }

    }



    /*
     * 2 - Atualizar tela
     */
    screenManager.update();



    /*
     * 3 - Renderizar
     */
    renderer.draw();

}



void UIEngine::show(
    UIScreen* screen
)
{

    screenManager.show(
        screen
    );


    renderer.setScreen(
        screen
    );

}



UIScreenManager& UIEngine::screens()
{
    return screenManager;
}


}