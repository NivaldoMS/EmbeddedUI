#ifndef EMBEDDEDUI_BUILDER_H
#define EMBEDDEDUI_BUILDER_H

#include "Menu.h"
#include "ValueNode.h"


namespace EmbeddedUI
{


class Builder
{

public:

    explicit Builder(
        Menu& menu
    );


    Builder& folder(
        const char* caption
    );


    Builder& value(
        const char* caption,
        ValueType type = ValueType::Integer
    );


    Builder& action(
        const char* caption
    );


    Builder& end();



private:

    Menu& _menu;

    Node* _current;


};


}


#endif