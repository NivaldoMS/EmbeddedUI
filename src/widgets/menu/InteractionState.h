#ifndef EMBEDDED_UI_INTERACTION_STATE_H
#define EMBEDDED_UI_INTERACTION_STATE_H


#include "Node.h"
#include "ValueNode.h"


namespace EmbeddedUI
{


enum class InteractionMode : uint8_t
{
    Browse = 0,
    Edit
};



class InteractionState
{

public:


    InteractionState();



    InteractionMode mode() const;



    void enterEdit(
        ValueNode* value
    );


    void leaveEdit();



    bool editing() const;



    ValueNode* valueNode() const;



private:


    InteractionMode _mode;


    ValueNode* _valueNode;


};


}


#endif