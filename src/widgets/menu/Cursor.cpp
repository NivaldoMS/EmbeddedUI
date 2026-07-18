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


}