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

    _current = root;

}



Node* Cursor::current() const
{
    return _current;
}



bool Cursor::moveNext()
{

    if(!_current)
        return false;



    if(_current->nextSibling())
    {

        _current =
            _current->nextSibling();


        return true;

    }


    return false;

}



bool Cursor::movePrevious()
{

    if(!_current)
        return false;



    if(_current->previousSibling())
    {

        _current =
            _current->previousSibling();


        return true;

    }


    return false;

}



bool Cursor::enter()
{

    if(!_current)
        return false;



    if(_current->firstChild())
    {

        _current =
            _current->firstChild();


        return true;

    }


    return false;

}



bool Cursor::back()
{

    if(!_current)
        return false;



    if(_current->parent())
    {

        _current =
            _current->parent();


        return true;

    }


    return false;

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


uint16_t Cursor::currentIndex() const
{

    if(!_current)
        return 0;


    uint16_t index = 0;

    Node* node = _current;


    while(node->previousSibling())
    {
        node = node->previousSibling();
        index++;
    }


    return index;

}

Node* Cursor::firstSibling() const
{

    if(!_current)
        return nullptr;


    Node* node = _current;


    while(node->previousSibling())
    {
        node = node->previousSibling();
    }


    return node;

}

}