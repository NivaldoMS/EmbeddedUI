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


    explicit Node(
        const char* caption = nullptr,
        NodeType type = NodeType::Folder
    );


    virtual ~Node();



    /**
     * Reconfigura o nó para reutilização pelo MenuBuilder.
     *
     * O nó é removido do pai atual e seus filhos são
     * desconectados antes da nova configuração.
     */
    void configure(
        const char* caption,
        NodeType type
    );



    Node* parent() const;

    Node* firstChild() const;

    Node* lastChild() const;

    Node* nextSibling() const;

    Node* previousSibling() const;



    bool append(
        Node* child
    );


    bool remove(
        Node* child
    );


    void clear();



    /**
     * Remove este nó de seu pai atual.
     */
    void detach();



    bool hasChildren() const;

    bool isRoot() const;

    uint16_t childCount() const;



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



protected:


    /**
     * Permite que classes derivadas, como ValueNode,
     * atualizem o tipo estrutural do nó.
     */
    void setType(
        NodeType type
    );



private:


    bool isAncestorOf(
        const Node* node
    ) const;



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