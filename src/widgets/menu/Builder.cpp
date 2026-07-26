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



Builder& Builder::begin(
    bool clearTree
)
{

    Node* root =
        _menu.root();


    if(!root)
    {
        _current =
            nullptr;


        return *this;
    }



    if(clearTree)
    {
        root->clear();
    }



    _menu.setCurrent(
        root
    );


    _current =
        root;



    return *this;

}



Builder& Builder::folder(
    Node& node
)
{

    if(node.type() != NodeType::Folder)
    {
        return *this;
    }



    if(!append(node))
    {
        return *this;
    }



    _current =
        &node;



    return *this;

}



Builder& Builder::folder(
    Node& node,
    const char* caption
)
{

    node.configure(
        caption,
        NodeType::Folder
    );


    return folder(
        node
    );

}



Builder& Builder::value(
    ValueNode& node
)
{

    if(node.type() != NodeType::Value)
    {
        return *this;
    }



    append(
        node
    );



    return *this;

}



Builder& Builder::integer(
    ValueNode& node,
    const char* caption,
    float minimum,
    float maximum,
    float step,
    float initialValue
)
{

    node.configure(
        caption,
        ValueType::Integer
    );


    node.setRange(
        minimum,
        maximum,
        step
    );


    node.setValue(
        initialValue
    );


    return value(
        node
    );

}



Builder& Builder::floating(
    ValueNode& node,
    const char* caption,
    float minimum,
    float maximum,
    float step,
    float initialValue
)
{

    node.configure(
        caption,
        ValueType::Float
    );


    node.setRange(
        minimum,
        maximum,
        step
    );


    node.setValue(
        initialValue
    );


    return value(
        node
    );

}



Builder& Builder::boolean(
    ValueNode& node,
    const char* caption,
    bool initialValue
)
{

    node.configure(
        caption,
        ValueType::Boolean
    );


    node.setRange(
        0.0f,
        1.0f,
        1.0f
    );


    node.setValue(
        initialValue
        ?
        1.0f
        :
        0.0f
    );


    return value(
        node
    );

}



Builder& Builder::action(
    ActionNode& node
)
{

    if(!_current)
    {

        return *this;

    }


    append(
        node
    );


    return *this;

}



Builder& Builder::action(
    ActionNode& node,
    const char* caption
)
{

    if(!_current)
    {

        return *this;

    }


    node.configure(
        caption
    );


    append(
        node
    );


    return *this;

}



Builder& Builder::action(
    ActionNode& node,
    const char* caption,
    ActionNode::Callback callback,
    void* context
)
{

    if(!_current)
    {

        return *this;

    }


    node.configure(
        caption,
        callback,
        context
    );


    append(
        node
    );


    return *this;

}


Builder& Builder::separator(
    Node& node
)
{

    node.configure(
        nullptr,
        NodeType::Separator
    );


    append(
        node
    );



    return *this;

}



Builder& Builder::end()
{

    if(!_current)
    {
        return *this;
    }



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



bool Builder::append(
    Node& node
)
{

    if(!_current)
    {
        return false;
    }



    return _current->append(
        &node
    );

}


}