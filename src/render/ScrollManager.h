#ifndef EMBEDDED_UI_SCROLL_MANAGER_H
#define EMBEDDED_UI_SCROLL_MANAGER_H


#include <Arduino.h>


namespace EmbeddedUI
{


class ScrollManager
{

public:


    ScrollManager();



    void configure(
        uint8_t visibleLines
    );



    void update(
        uint16_t selectedIndex,
        uint16_t totalItems
    );



    uint16_t firstVisible() const;



    uint8_t visibleLines() const;



private:


    uint16_t _firstVisible;


    uint8_t _visibleLines;


};


}


#endif