#ifndef EMBEDDEDUI_VALUE_NODE_H
#define EMBEDDEDUI_VALUE_NODE_H


#include "Node.h"


namespace EmbeddedUI
{


enum class ValueType : uint8_t
{
    Integer,
    Float,
    Boolean,
    List
};


class ValueNode : public Node
{

public:

    using ChangeCallback =
        void (*)(
            ValueNode& node,
            float value,
            void* context
        );


    explicit ValueNode(
        const char* caption = nullptr,
        ValueType type = ValueType::Integer
    );



    void configure(
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

    void setChangeCallback(
        ChangeCallback callback,
        void* context = nullptr
    );



    bool hasChangeCallback() const;

private:

    void notifyChanged();

    float defaultStep() const;



    ValueType _valueType;


    float _value;

    float _minimum;

    float _maximum;

    float _step;

    ChangeCallback _changeCallback;

    void* _changeContext;
    
};


}


#endif