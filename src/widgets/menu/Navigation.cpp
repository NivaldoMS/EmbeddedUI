#include "Navigation.h"


namespace EmbeddedUI
{


Navigation::Navigation(
    Cursor& cursor,
    InteractionState& state
)
:
_cursor(cursor),
_state(state)
{

}



void Navigation::next()
{
    if(!_state.editing())
    {
        _cursor.moveNext();
    }
    else
    {
        editNext();
    }
}



void Navigation::previous()
{
    if(!_state.editing())
    {
        _cursor.movePrevious();
    }
    else
    {
        editPrevious();
    }
}



bool Navigation::enter()
{

    if(_state.editing())
    {
        confirm();

        return true;
    }



    Node* node =
        _cursor.current();



    if(!node)
        return false;



    if(node->type() == NodeType::Value)
    {

        ValueNode* value =
            static_cast<ValueNode*>(node);


        _state.enterEdit(
            value
        );


        return true;
    }



    return _cursor.enter();

}



bool Navigation::back()
{

    if(_state.editing())
    {
        cancel();

        return true;
    }


    return _cursor.back();

}



void Navigation::editNext()
{

    ValueNode* value =
        _state.valueNode();


    if(value)
    {
        value->setValue(
            value->value()
            +
            value->step()
        );
    }

}



void Navigation::editPrevious()
{

    ValueNode* value =
        _state.valueNode();


    if(value)
    {
        value->setValue(
            value->value()
            -
            value->step()
        );
    }

}



void Navigation::confirm()
{
    _state.leaveEdit();
}



void Navigation::cancel()
{
    _state.leaveEdit();
}



void Navigation::handleEvent(
    const UIEvent& event
)
{

    switch(event.type)
    {


        case UIEventType::ENCODER_CW:

            next();

        break;



        case UIEventType::ENCODER_CCW:

            previous();

        break;



        case UIEventType::BUTTON_ENTER:

            enter();

        break;



        case UIEventType::BUTTON_BACK:

            back();

        break;



        default:

        break;

    }

}


}