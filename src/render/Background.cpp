#include "Background.h"

#include "../drivers/display/DisplayDriver.h"


namespace EmbeddedUI
{


Background::Background()
:
_bitmap(nullptr)
{

}



void Background::setBitmap(
    const Bitmap* bitmap
)
{

    _bitmap =
        bitmap;

}



void Background::clear()
{

    _bitmap =
        nullptr;

}



const Bitmap* Background::bitmap() const
{

    return _bitmap;

}



void Background::draw(
    DisplayDriver& display
) const
{

    if(!_bitmap)
        return;



    display.drawBitmap(
        0,
        0,
        *_bitmap
    );

}


}