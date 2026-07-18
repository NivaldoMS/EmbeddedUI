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
    const char* caption
)
{
    Node* node =
        new Node(
            caption,
            NodeType::Folder
        );


    _current->append(node);

    _current = node;


    return *this;
}



Builder& Builder::value(
    const char* caption,
    ValueType type
)
{
    ValueNode* node =
        new ValueNode(
            caption,
            type
        );


    _current->append(node);


    return *this;
}



Builder& Builder::action(
    const char* caption
)
{
    Node* node =
        new Node(
            caption,
            NodeType::Action
        );


    _current->append(node);


    return *this;
}



Builder& Builder::end()
{
    if(_current->parent())
    {
        _current =
            _current->parent();
    }


    return *this;
}


}