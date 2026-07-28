#ifndef MENU_APPLICATION_H
#define MENU_APPLICATION_H


#include <EmbeddedUI.h>

#include "InformationScreen.h"
#include "ResetScreen.h"


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


    void finishStartup();


    Menu& menu();


    const Menu& menu() const;



    Node* selectedNode();



    Node* editingNode();



    Node* executingNode();



    void startExecuting(
        Node* node
    );



    void stopExecuting();



private:


    void configureTheme();



    void buildMenu();



    static void handleInformation(
        ActionNode& node,
        void* context
    );


    static void handleReset(
        ActionNode& node,
        void* context
    );

    static void handleBrightnessChanged(
        ValueNode& node,
        float value,
        void* context
    );

    static void performResetTask(
        void* context
    );

    DisplayDriver& _display;


    InputManager _input;


    Theme _theme;


    Font _font;


    Render _render;


    Engine _engine;


    Menu _menu;

    MenuScreen _menuScreen;

    SplashScreen _splashScreen;
    
    ApplicationScreens::InformationScreen _informationScreen;

    ApplicationScreens::ResetScreen _resetScreen;


    Node _audioFolder;


    ValueNode _volumeValue;
    
    ValueNode _balValue;

    ValueNode _bassValue;

    ValueNode _midValue;

    ValueNode _trebleValue;

    ValueNode _enabledValue;

    ListNode _lowFreqValue;

    ListNode _highFreqValue;


    Node _displayFolder;


    ValueNode _brightnessValue;


    ValueNode _contrastValue;


    Node _systemFolder;


    ActionNode _informationAction;


    ActionNode _resetAction;


    Builder _builder;


    Node* _executingNode;


};


#endif