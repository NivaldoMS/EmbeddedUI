#include "InteractionState.h"


namespace EmbeddedUI
{


InteractionState::InteractionState()
:
_mode(InteractionMode::Browse),
_valueNode(nullptr)
{

}



InteractionMode InteractionState::mode() const
{
    return _mode;
}



void InteractionState::enterEdit(
    ValueNode* value
)
{

    if(!value)
        return;


    _valueNode = value;

    _mode =
        InteractionMode::Edit;

}



void InteractionState::leaveEdit()
{

    _valueNode = nullptr;

    _mode =
        InteractionMode::Browse;

}



bool InteractionState::editing() const
{
    return
        _mode == InteractionMode::Edit;
}



ValueNode* InteractionState::valueNode() const
{
    return _valueNode;
}


}