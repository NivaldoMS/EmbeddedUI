#ifndef EMBEDDED_UI_MENU_APPLICATION_H
#define EMBEDDED_UI_MENU_APPLICATION_H


#include <EmbeddedUI.h>


using namespace EmbeddedUI;


class MenuApplication
{

public:


    explicit MenuApplication(
        WebSocketDisplay& display
    );


    void begin(
        InputDevice& inputDevice
    );


    void update();


private:


    void configureValues();


    void buildMenu();


    WebSocketDisplay& _display;


    InputManager _input;


    Theme _theme;


    Font _font;


    Renderer _renderer;


    Engine _engine;


    Menu _menu;


    MenuScreen _menuScreen;


    Node _audioFolder;


    ValueNode _volumeValue;


    ValueNode _bassValue;


    ValueNode _enabledValue;


    Node _displayFolder;


    ValueNode _brightnessValue;


    Node _systemFolder;


    Node _informationAction;


    Node _resetAction;


    Builder _builder;


};


#endif