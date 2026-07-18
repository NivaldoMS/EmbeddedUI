#ifndef EMBEDDEDUI_NODE_H
#define EMBEDDEDUI_NODE_H

#include <Arduino.h>

namespace EmbeddedUI
{

enum class NodeType : uint8_t
{
    Folder,
    Action,
    Value,
    Separator
};


class Node
{

public:

    Node(
        const char* caption = nullptr,
        NodeType type = NodeType::Folder
    );


    virtual ~Node();



    // Hierarquia
    bool isRoot() const;

    Node* parent() const;

    Node* firstChild() const;

    Node* lastChild() const;

    Node* nextSibling() const;

    Node* previousSibling() const;



    // Manipulação

    bool append(Node* child);

    bool remove(Node* child);

    void clear();



    // Consulta

    bool hasChildren() const;

    uint16_t childCount() const;



    // Dados

    const char* caption() const;

    void setCaption(
        const char* text
    );


    NodeType type() const;



    bool isVisible() const;

    void setVisible(
        bool value
    );


    bool isEnabled() const;

    void setEnabled(
        bool value
    );



private:

    NodeType _type;

    const char* _caption;


    bool _visible;

    bool _enabled;


    Node* _parent;

    Node* _firstChild;

    Node* _lastChild;


    Node* _previousSibling;

    Node* _nextSibling;


    uint16_t _childCount;

};


}

#endif