#include "Node.h"


namespace EmbeddedUI
{


Node::Node(
    const char* caption,
    NodeType type
)
:
_type(type),
_caption(caption),
_visible(true),
_enabled(true),
_parent(nullptr),
_firstChild(nullptr),
_lastChild(nullptr),
_previousSibling(nullptr),
_nextSibling(nullptr),
_childCount(0)
{

}



Node::~Node()
{

    /*
     * Node não é proprietário dos filhos.
     * Apenas desfaz os vínculos da árvore.
     */

    clear();



    if(_parent)
    {
        _parent->remove(
            this
        );
    }

}



Node* Node::parent() const
{
    return _parent;
}



Node* Node::firstChild() const
{
    return _firstChild;
}



Node* Node::lastChild() const
{
    return _lastChild;
}



Node* Node::nextSibling() const
{
    return _nextSibling;
}



Node* Node::previousSibling() const
{
    return _previousSibling;
}



bool Node::append(
    Node* child
)
{

    if(!child)
        return false;



    if(child == this)
        return false;



    /*
     * Impede ciclos:
     * um ancestral não pode ser inserido
     * como filho de seu descendente.
     */
    if(child->isAncestorOf(this))
        return false;



    /*
     * O mesmo nó não pode pertencer
     * simultaneamente a dois pais.
     */
    if(child->_parent)
        return false;



    child->_parent =
        this;


    child->_previousSibling =
        _lastChild;


    child->_nextSibling =
        nullptr;



    if(_lastChild)
    {
        _lastChild->_nextSibling =
            child;
    }
    else
    {
        _firstChild =
            child;
    }



    _lastChild =
        child;


    _childCount++;



    return true;

}



bool Node::remove(
    Node* child
)
{

    if(!child)
        return false;



    if(child->_parent != this)
        return false;



    if(child->_previousSibling)
    {
        child->_previousSibling->_nextSibling =
            child->_nextSibling;
    }
    else
    {
        _firstChild =
            child->_nextSibling;
    }



    if(child->_nextSibling)
    {
        child->_nextSibling->_previousSibling =
            child->_previousSibling;
    }
    else
    {
        _lastChild =
            child->_previousSibling;
    }



    child->_parent =
        nullptr;


    child->_previousSibling =
        nullptr;


    child->_nextSibling =
        nullptr;



    if(_childCount > 0)
    {
        _childCount--;
    }



    return true;

}



void Node::clear()
{

    Node* child =
        _firstChild;



    while(child)
    {

        Node* next =
            child->_nextSibling;



        child->_parent =
            nullptr;


        child->_previousSibling =
            nullptr;


        child->_nextSibling =
            nullptr;



        child =
            next;

    }



    _firstChild =
        nullptr;


    _lastChild =
        nullptr;


    _childCount =
        0;

}



bool Node::hasChildren() const
{
    return _firstChild != nullptr;
}



bool Node::isRoot() const
{
    return _parent == nullptr;
}



uint16_t Node::childCount() const
{
    return _childCount;
}



const char* Node::caption() const
{
    return _caption;
}



void Node::setCaption(
    const char* text
)
{
    _caption =
        text;
}



NodeType Node::type() const
{
    return _type;
}



bool Node::isVisible() const
{
    return _visible;
}



void Node::setVisible(
    bool value
)
{
    _visible =
        value;
}



bool Node::isEnabled() const
{
    return _enabled;
}



void Node::setEnabled(
    bool value
)
{
    _enabled =
        value;
}



bool Node::isAncestorOf(
    const Node* node
) const
{

    if(!node)
        return false;



    const Node* current =
        node->_parent;



    while(current)
    {

        if(current == this)
            return true;


        current =
            current->_parent;

    }



    return false;

}


}