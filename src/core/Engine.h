#ifndef EMBEDDED_UI_ENGINE_H
#define EMBEDDED_UI_ENGINE_H


#include "ScreenManager.h"

#include "../render/Renderer.h"

#include "../input/InputManager.h"

#include "EventQueue.h"



namespace EmbeddedUI
{


class UIEngine
{

public:


    UIEngine();



    void begin(
        UIScreen* initialScreen,
        UIDisplayDriver& display,
        UIInputManager& input
    );



    void update();



    void draw();



    void show(
        UIScreen* screen
    );



    UIScreenManager& screens();



private:


    UIScreenManager screenManager;


    Renderer* renderer;


    UIInputManager* input;


    EventQueue eventQueue;


};


}


#endif