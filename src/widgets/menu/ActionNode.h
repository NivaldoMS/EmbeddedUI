#ifndef EMBEDDEDUI_ACTION_NODE_H
#define EMBEDDEDUI_ACTION_NODE_H


#include "Node.h"


namespace EmbeddedUI
{


class ActionNode : public Node
{

public:


    using Callback =
        void (*)(
            ActionNode& node,
            void* context
        );



    explicit ActionNode(
        const char* caption = nullptr
    );



    void configure(
        const char* caption,
        Callback callback = nullptr,
        void* context = nullptr
    );



    void setCallback(
        Callback callback,
        void* context = nullptr
    );



    bool execute();



    bool hasCallback() const;



private:


    Callback _callback;


    void* _context;


};


}


#endif