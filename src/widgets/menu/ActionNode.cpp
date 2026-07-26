#include "ActionNode.h"


namespace EmbeddedUI
{


ActionNode::ActionNode(
    const char* caption
)
:
Node(
    caption,
    NodeType::Action
),
_callback(nullptr),
_context(nullptr)
{

}



void ActionNode::configure(
    const char* caption,
    Callback callback,
    void* context
)
{

    Node::configure(
        caption,
        NodeType::Action
    );


    _callback =
        callback;


    _context =
        context;

}



void ActionNode::setCallback(
    Callback callback,
    void* context
)
{

    _callback =
        callback;


    _context =
        context;

}

// bool ActionNode::execute()
// {

//     Serial.println(
//         F("[ActionNode] execute()")
//     );


//     if(_callback == nullptr)
//     {

//         Serial.println(
//             F("[ActionNode] callback ausente")
//         );


//         return false;

//     }


//     Serial.println(
//         F("[ActionNode] chamando callback")
//     );


//     _callback(
//         *this,
//         _context
//     );


//     return true;

// }

bool ActionNode::execute()
{

    if(_callback == nullptr)
    {

        return false;

    }


    _callback(
        *this,
        _context
    );


    return true;

}



bool ActionNode::hasCallback() const
{

    return
        _callback != nullptr;

}


}