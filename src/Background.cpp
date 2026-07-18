#include "Background.h"

#include "DisplayDriver.h"


namespace EmbeddedUI
{


UIBackground::UIBackground()
:
bitmap(nullptr)
{

}



void UIBackground::setBitmap(
    const UIBitmap* bitmap
)
{
    this->bitmap = bitmap;
}



void UIBackground::clear()
{
    bitmap = nullptr;
}



void UIBackground::draw(
    UIDisplayDriver* display
)
{

    if(!bitmap)
        return;


    /*
     * O desenho real depende do driver.
     *
     * O DisplayDriver receberá suporte
     * a bitmap no próximo refinamento.
     */


}



}