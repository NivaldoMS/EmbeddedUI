#include "Layout.h"


namespace EmbeddedUI
{


Layout::Layout(
    const Theme& theme
)
:
_theme(theme)
{

}



uint16_t Layout::lineY(
    uint8_t line
) const
{

    return
        _theme.marginTop
        +
        (
            line
            *
            _theme.lineHeight
        );

}



int16_t Layout::valueX(
    uint16_t displayWidth
) const
{

    return
        displayWidth
        -
        _theme.marginLeft
        -
        32;

}



Rect Layout::itemRect(
    uint8_t line,
    uint16_t displayWidth
) const
{

    Rect rect;


    rect.x =
        0;


    rect.y =
        lineY(line)
        -
        _theme.lineHeight
        +
        2;


    rect.width =
        displayWidth;


    rect.height =
        _theme.lineHeight;



    return rect;

}


}