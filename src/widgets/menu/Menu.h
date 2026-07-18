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


    Node* current();


    void setCurrent(
        Node* node
    );


private:

    Node _root;

    Node* _current;

};


}


#endif