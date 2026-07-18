#include "Menu.h"


namespace EmbeddedUI
{


Menu::Menu()
:
_root(
    "Root",
    NodeType::Folder
),
_current(
    &_root
)
{

}



Node* Menu::root()
{
    return &_root;
}



Node* Menu::current()
{
    return _current;
}



void Menu::setCurrent(
    Node* node
)
{

    if(node)
    {
        _current = node;
    }

}


}