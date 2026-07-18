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
_value(0.0f),
_minimum(0.0f),
_maximum(100.0f),
_step(1.0f)
{

}



void ValueNode::setRange(
    float minimum,
    float maximum,
    float step
)
{

    if(minimum > maximum)
    {
        const float temporary =
            minimum;


        minimum =
            maximum;


        maximum =
            temporary;
    }



    _minimum =
        minimum;


    _maximum =
        maximum;


    _step =
        step > 0.0f
        ?
        step
        :
        1.0f;



    setValue(
        _value
    );

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
        value =
            _minimum;
    }



    if(value > _maximum)
    {
        value =
            _maximum;
    }



    if(_valueType == ValueType::Boolean)
    {
        _value =
            value > 0.0f
            ?
            1.0f
            :
            0.0f;


        return;
    }



    _value =
        value;

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