#include "Navigation.h"

#include "ActionNode.h"

#include <Arduino.h>


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



    if(node == nullptr)
    {

        return false;

    }



    if(!node->isEnabled())
    {

        return false;

    }



    switch(node->type())
    {

        case NodeType::Value:

            _state.enterEdit(
                static_cast<ValueNode*>(
                    node
                )
            );


            return true;



        case NodeType::Action:
        {

            ActionNode* actionNode =
                static_cast<ActionNode*>(
                    node
                );


            return
                actionNode->execute();

        }



        case NodeType::Folder:

            return
                _cursor.enter();



        case NodeType::Separator:

        default:

            return false;

    }

}

bool Navigation::back()
{

    /*
     * BACK durante a edição restaura
     * o valor original.
     */
    if(_state.editing())
    {

        cancel();

        return true;

    }



    return
        _cursor.back();

}



void Navigation::editNext()
{

    ValueNode* value =
        _state.valueNode();



    if(!value)
    {

        return;

    }



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
    {

        return;

    }



    value->setValue(
        value->value()
        -
        value->step()
    );

}



void Navigation::confirm()
{

    /*
     * Mantém o valor atualmente editado.
     */
    _state.confirmEdit();

}



void Navigation::cancel()
{

    /*
     * Restaura o valor que existia
     * antes do início da edição.
     */
    _state.cancelEdit();

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