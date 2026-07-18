#include "ValueNode.h"


namespace EmbeddedUI
{


ValueNode::ValueNode(
    const char* caption,
    ValueType type
)
:
Node(
    caption,
    NodeType::Value
),
_valueType(type),
_value(0),
_minimum(0),
_maximum(100),
_step(1)
{

}



void ValueNode::setRange(
    float minimum,
    float maximum,
    float step
)
{

    _minimum = minimum;

    _maximum = maximum;

    _step = step;



    if(_value < _minimum)
    {
        _value = _minimum;
    }



    if(_value > _maximum)
    {
        _value = _maximum;
    }

}



float ValueNode::value() const
{
    return _value;
}



void ValueNode::setValue(
    float value
)
{

    if(value < _minimum)
    {
        value = _minimum;
    }



    if(value > _maximum)
    {
        value = _maximum;
    }



    _value = value;

}



float ValueNode::minimum() const
{
    return _minimum;
}



float ValueNode::maximum() const
{
    return _maximum;
}



float ValueNode::step() const
{
    return _step;
}



ValueType ValueNode::valueType() const
{
    return _valueType;
}


}