#include "ScrollManager.h"


namespace EmbeddedUI
{


ScrollManager::ScrollManager()
:
_firstVisible(0),
_visibleLines(4)
{

}



void ScrollManager::configure(
    uint8_t visibleLines
)
{
    _visibleLines = visibleLines;
}



void ScrollManager::update(
    uint16_t selectedIndex,
    uint16_t totalItems
)
{

    if(totalItems <= _visibleLines)
    {
        _firstVisible = 0;

        return;
    }



    if(selectedIndex < _firstVisible)
    {
        _firstVisible =
            selectedIndex;
    }



    if(selectedIndex >=
       (_firstVisible + _visibleLines))
    {

        _firstVisible =
            selectedIndex
            -
            _visibleLines
            +
            1;

    }



    if(_firstVisible +
       _visibleLines >
       totalItems)
    {
        _firstVisible =
            totalItems
            -
            _visibleLines;
    }

}



uint16_t ScrollManager::firstVisible() const
{
    return _firstVisible;
}



uint8_t ScrollManager::visibleLines() const
{
    return _visibleLines;
}


}