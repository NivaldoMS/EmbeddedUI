#ifndef EMBEDDED_UI_CURSOR_H
#define EMBEDDED_UI_CURSOR_H


#include "Node.h"


namespace EmbeddedUI
{


class Cursor
{

public:


    Cursor();



    void attach(
        Node* root
    );



    Node* current() const;



    bool moveNext();



    bool movePrevious();



    bool enter();



    bool back();



private:


    Node* _current;


};


}


#endif