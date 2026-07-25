#ifndef MENU_HIERARCHY_MONITOR_APPLICATION_H
#define MENU_HIERARCHY_MONITOR_APPLICATION_H


#include <EmbeddedUI.h>


using namespace EmbeddedUI;


class MenuApplication
{

public:


    explicit MenuApplication(
        DisplayDriver& display
    );


    void begin(
        InputDevice& inputDevice
    );


    void update();


    Menu& menu();


    Node* selectedNode();


    Node* editingNode();


    Node* executingNode();


    void startExecuting(
        Node* node
    );


    void stopExecuting();


private:


    void configureValues();


    void buildMenu();


    DisplayDriver& _display;


    InputManager _input;


    Theme _theme;


    Font _font;


    Render _render;


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


    Node* _executingNode;


};


#endif