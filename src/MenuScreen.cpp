#include "MenuScreen.h"


namespace EmbeddedUI
{


UIMenuScreen::UIMenuScreen()
:
UIScreen(),
root(nullptr),
current(nullptr),
cursor(0)
{

    componentType = UIComponentType::MENU;

}



void UIMenuScreen::setRoot(
    UIItem* item
)
{
    root = item;
    current = item;
    cursor = 0;
}



UIItem* UIMenuScreen::currentItem()
{
    return current;
}

uint8_t UIMenuScreen::cursorPosition() const
{
    return cursor;
}

UIItem* UIMenuScreen::selectedItem()
{

    if(!current)
        return nullptr;


    return current->child(cursor);

}



void UIMenuScreen::moveUp()
{

    if(!current)
        return;


    if(cursor > 0)
        cursor--;

}



void UIMenuScreen::moveDown()
{

    if(!current)
        return;


    if(cursor + 1 < current->childCount())
        cursor++;

}



void UIMenuScreen::enter()
{

    UIItem* item = selectedItem();


    if(!item)
        return;



    if(item->type() == UIItemType::SUBMENU)
    {
        current = item;
        cursor = 0;
        return;
    }



    if(item->type() == UIItemType::ACTION)
    {
        item->execute();
        return;
    }



    if(item->getValue())
    {
        item->getValue()->beginEdit();
        state = UIState::EDITING;
    }

}



void UIMenuScreen::back()
{

    if(!current)
        return;


    if(state == UIState::EDITING)
    {
        UIItem* item = selectedItem();

        if(item && item->getValue())
        {
            item->getValue()->cancel();
        }

        state = UIState::ACTIVE;
        return;
    }



    if(current->parent())
    {
        current = current->parent();
        cursor = 0;
    }

}



UIResult UIMenuScreen::handleEvent(
    const UIEvent& event
)
{

    switch(event.type)
    {

        case UIEventType::ENCODER_CW:

            if(state == UIState::EDITING)
            {
                UIItem* item = selectedItem();

                if(item && item->getValue())
                    item->getValue()->increase();
            }
            else
            {
                moveDown();
            }

            return UIResult::HANDLED;



        case UIEventType::ENCODER_CCW:

            if(state == UIState::EDITING)
            {
                UIItem* item = selectedItem();

                if(item && item->getValue())
                    item->getValue()->decrease();
            }
            else
            {
                moveUp();
            }

            return UIResult::HANDLED;



        case UIEventType::BUTTON_ENTER:

            enter();
            return UIResult::HANDLED;



        case UIEventType::BUTTON_BACK:

            back();
            return UIResult::HANDLED;



        default:
            break;
    }


    return UIResult::NONE;
}


}