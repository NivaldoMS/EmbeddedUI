#ifndef EMBEDDEDUI_MENU_H
#define EMBEDDEDUI_MENU_H


#include "Node.h"


namespace EmbeddedUI
{


class Menu
{

public:


    Menu();



    Node* root();



private:


    Node _root;


};


}


#endif