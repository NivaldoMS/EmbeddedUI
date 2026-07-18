#include "Builder.h"


namespace EmbeddedUI
{


Builder::Builder(
    Menu& menu
)
:
_menu(menu),
_current(menu.root())
{

}



Builder& Builder::folder(
    Node& node
)
{

    if(!_current)
        return *this;



    if(node.type() != NodeType::Folder)
        return *this;



    if(!_current->append(&node))
        return *this;



    _current =
        &node;



    return *this;

}



Builder& Builder::value(
    ValueNode& node
)
{

    if(!_current)
        return *this;



    _current->append(
        &node
    );



    return *this;

}



Builder& Builder::action(
    Node& node
)
{

    if(!_current)
        return *this;



    if(node.type() != NodeType::Action)
        return *this;



    _current->append(
        &node
    );



    return *this;

}



Builder& Builder::end()
{

    if(!_current)
        return *this;



    Node* parent =
        _current->parent();



    if(parent)
    {
        _current =
            parent;
    }



    return *this;

}



Node* Builder::current() const
{

    return _current;

}


}