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



int16_t Layout::lineY(
    uint8_t line
) const
{

    return
        static_cast<int16_t>(
            _theme.marginTop
        )
        +
        (
            static_cast<int16_t>(line)
            *
            static_cast<int16_t>(
                _theme.lineHeight
            )
        );

}



int16_t Layout::valueX(
    uint16_t displayWidth
) const
{

    return
        static_cast<int16_t>(
            displayWidth
        )
        -
        static_cast<int16_t>(
            _theme.marginLeft
        )
        -
        static_cast<int16_t>(
            _theme.valueWidth
        );

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
        static_cast<int16_t>(
            _theme.lineHeight
        )
        +
        2;



    rect.width =
        static_cast<int16_t>(
            displayWidth
        );



    rect.height =
        static_cast<int16_t>(
            _theme.lineHeight
        );



    return rect;

}



Rect Layout::valueRect(
    uint8_t line,
    uint16_t displayWidth
) const
{

    Rect rect;



    rect.x =
        valueX(
            displayWidth
        )
        -
        2;



    rect.y =
        lineY(line)
        -
        static_cast<int16_t>(
            _theme.lineHeight
        )
        +
        2;



    rect.width =
        static_cast<int16_t>(
            _theme.valueWidth
        )
        +
        2;



    rect.height =
        static_cast<int16_t>(
            _theme.lineHeight
        );



    return rect;

}


}