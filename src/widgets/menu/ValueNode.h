#ifndef EMBEDDEDUI_VALUE_NODE_H
#define EMBEDDEDUI_VALUE_NODE_H

#include "Node.h"


namespace EmbeddedUI
{


enum class ValueType : uint8_t
{
    Integer,
    Float,
    Boolean
};



class ValueNode : public Node
{

public:


    ValueNode(
        const char* caption,
        ValueType type
    );


    void setRange(
        float minimum,
        float maximum,
        float step
    );


    float value() const;


    void setValue(
        float value
    );


    float minimum() const;


    float maximum() const;


    float step() const;


    ValueType valueType() const;



private:


    ValueType _valueType;


    float _value;

    float _minimum;

    float _maximum;

    float _step;


};


}


#endif