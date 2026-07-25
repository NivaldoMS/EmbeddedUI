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

    configure(
        caption,
        type
    );

}



void ValueNode::configure(
    const char* caption,
    ValueType type
)
{

    Node::configure(
        caption,
        NodeType::Value
    );


    _valueType =
        type;


    _value =
        0.0f;



    switch(_valueType)
    {

        case ValueType::Integer:

            _minimum =
                0.0f;


            _maximum =
                100.0f;


            _step =
                1.0f;

            break;



        case ValueType::Float:

            _minimum =
                0.0f;


            _maximum =
                1.0f;


            _step =
                0.1f;

            break;



        case ValueType::Boolean:

            _minimum =
                0.0f;


            _maximum =
                1.0f;


            _step =
                1.0f;

            break;

    }

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
        defaultStep();



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



    switch(_valueType)
    {

        case ValueType::Boolean:

            _value =
                value > 0.0f
                ?
                1.0f
                :
                0.0f;

            return;



        case ValueType::Integer:

            _value =
                static_cast<float>(
                    static_cast<int32_t>(
                        value
                    )
                );

            return;



        case ValueType::Float:

            _value =
                value;

            return;

    }

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



float ValueNode::defaultStep() const
{

    switch(_valueType)
    {

        case ValueType::Float:

            return 0.1f;



        case ValueType::Integer:

        case ValueType::Boolean:

        default:

            return 1.0f;

    }

}


}