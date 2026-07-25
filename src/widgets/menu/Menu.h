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


    const Node* root() const;



    Node* current() const;



    bool setCurrent(
        Node* node
    );



    void reset();



private:


    bool contains(
        const Node* node
    ) const;



    Node _root;


    Node* _current;


};


}


#endif