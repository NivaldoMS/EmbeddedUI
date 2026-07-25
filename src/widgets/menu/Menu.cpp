#include "Menu.h"


namespace EmbeddedUI
{


Menu::Menu()
:
_root(
    nullptr,
    NodeType::Folder
),
_current(
    &_root
)
{

}



Node* Menu::root()
{

    return
        &_root;

}



const Node* Menu::root() const
{

    return
        &_root;

}



Node* Menu::current() const
{

    return
        _current;

}



bool Menu::setCurrent(
    Node* node
)
{

    if(node == nullptr)
    {

        return false;

    }



    if(!contains(node))
    {

        return false;

    }



    _current =
        node;



    return true;

}



void Menu::reset()
{

    _root.clear();


    _current =
        &_root;

}



bool Menu::contains(
    const Node* node
) const
{

    if(node == nullptr)
    {

        return false;

    }



    const Node* current =
        node;



    while(current->parent() != nullptr)
    {

        current =
            current->parent();

    }



    return
        current == &_root;

}


}