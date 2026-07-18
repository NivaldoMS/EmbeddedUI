#include "Cursor.h"


namespace EmbeddedUI
{


Cursor::Cursor()
:
_current(nullptr)
{

}



void Cursor::attach(
    Node* root
)
{

    _current =
        root;

}



Node* Cursor::current() const
{

    return _current;

}



bool Cursor::moveNext()
{

    if(!_current)
        return false;



    Node* next =
        _current->nextSibling();



    if(!next)
        return false;



    _current =
        next;



    return true;

}



bool Cursor::movePrevious()
{

    if(!_current)
        return false;



    Node* previous =
        _current->previousSibling();



    if(!previous)
        return false;



    _current =
        previous;



    return true;

}



bool Cursor::enter()
{

    if(!_current)
        return false;



    Node* child =
        _current->firstChild();



    if(!child)
        return false;



    _current =
        child;



    return true;

}



bool Cursor::back()
{

    if(!_current)
        return false;



    Node* parent =
        _current->parent();



    if(!parent)
        return false;



    _current =
        parent;



    return true;

}



uint16_t Cursor::index() const
{

    if(!_current)
        return 0;



    uint16_t position = 0;



    Node* node =
        _current->previousSibling();



    while(node)
    {

        position++;



        node =
            node->previousSibling();

    }



    return position;

}



uint16_t Cursor::siblingCount() const
{

    Node* node =
        firstSibling();



    uint16_t count = 0;



    while(node)
    {

        count++;



        node =
            node->nextSibling();

    }



    return count;

}



Node* Cursor::firstSibling() const
{

    if(!_current)
        return nullptr;



    Node* node =
        _current;



    while(node->previousSibling())
    {

        node =
            node->previousSibling();

    }



    return node;

}


}