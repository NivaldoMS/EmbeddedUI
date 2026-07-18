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

    if(_state.editing())
    {

        editNext();

        return;

    }



    _cursor.moveNext();

}



void Navigation::previous()
{

    if(_state.editing())
    {

        editPrevious();

        return;

    }



    _cursor.movePrevious();

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



    if(!node->isEnabled())
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



    if(!value)
        return;



    value->setValue(
        value->value()
        +
        value->step()
    );

}



void Navigation::editPrevious()
{

    ValueNode* value =
        _state.valueNode();



    if(!value)
        return;



    value->setValue(
        value->value()
        -
        value->step()
    );

}



void Navigation::confirm()
{

    _state.leaveEdit();

}



void Navigation::cancel()
{

    /*
     * O estado atual não mantém uma cópia
     * do valor anterior. Portanto, cancelar
     * encerra a edição sem restaurar o valor.
     */

    _state.leaveEdit();

}



void Navigation::handleEvent(
    const Event& event
)
{

    switch(event.type)
    {

        case EventType::ENCODER_CW:

            next();

        break;



        case EventType::ENCODER_CCW:

            previous();

        break;



        case EventType::BUTTON_ENTER:

            enter();

        break;



        case EventType::BUTTON_BACK:

            back();

        break;



        default:

        break;

    }

}


}