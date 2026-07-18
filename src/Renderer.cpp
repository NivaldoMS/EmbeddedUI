#include "Renderer.h"


namespace EmbeddedUI
{


UIRenderer::UIRenderer()
:
display(nullptr),
screen(nullptr)
{

}



void UIRenderer::setDisplay(
    UIDisplayDriver* display
)
{
    this->display = display;
}



void UIRenderer::setScreen(
    UIScreen* screen
)
{
    this->screen = screen;
}



void UIRenderer::draw()
{

    if(!display || !screen)
        return;



    display->clear();



    if(screen->type() == UIComponentType::MENU)
    {
        drawMenu(
            static_cast<UIMenuScreen*>(screen)
        );
    }



    display->refresh();

}



void UIRenderer::drawMenu(
    UIMenuScreen* menu
)
{

    UIItem* current = menu->currentItem();


    if(!current)
        return;



    uint8_t count = current->childCount();



    int16_t y = 15;



    for(uint8_t i = 0; i < count; i++)
    {

        UIItem* item = current->child(i);


        if(!item)
            continue;

        display->drawText(
            0,
            10,
            "EmbeddedUI"
        );

        display->drawText(
            5,
            y,
            item->title()
        );



        y += 12;

    }


}


}