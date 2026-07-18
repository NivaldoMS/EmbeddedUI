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

    background.draw(display);


    if(screen->type() == UIComponentType::MENU)
    {
        drawMenu(
            static_cast<UIMenuScreen*>(screen)
        );
    }



    display->refresh();

}

void UIRenderer::setBackground(
    const UIBitmap* bitmap
)
{
    background.setBitmap(bitmap);
}

void UIRenderer::drawMenu(
    UIMenuScreen* menu
)
{

    UIItem* current =
        menu->currentItem();



    if(!current)
        return;



    const uint8_t visibleLines = 8;


    uint8_t selected =
        menu->cursorPosition();



    uint8_t first =
        0;



    if(selected >= visibleLines)
    {
        first =
            selected - visibleLines + 1;
    }



    int16_t y = 14;



    for(
        uint8_t i = first;
        i < current->childCount()
        &&
        i < first + visibleLines;
        i++
    )
    {

        UIItem* item =
            current->child(i);



        if(!item)
            continue;



        /*
         * Cursor
         */
        if(i == selected)
        {

            display->fillRect(
                0,
                y - 10,
                display->width(),
                12
            );


        }



        /*
         * Nome do item
         */
        display->drawText(
            4,
            y,
            item->title()
        );



        /*
         * Valor
         */
        if(item->getValue())
        {

            display->drawText(
                90,
                y,
                item->getValue()->text()
            );

        }



        y += 14;

    }


}

}