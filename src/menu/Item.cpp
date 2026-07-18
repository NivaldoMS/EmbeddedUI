#include "Item.h"


namespace EmbeddedUI
{


UIItem::UIItem(
    const char* title,
    UIItemType type
)
:
itemTitle(title),
itemType(type),
value(nullptr),
parentItem(nullptr),
childrenCount(0),
callback(nullptr),
visibilityCallback(nullptr),
enabledCallback(nullptr)
{

    for(uint8_t i = 0; i < MAX_CHILDREN; i++)
    {
        children[i] = nullptr;
    }

}



UIItem::~UIItem()
{

}



void UIItem::setValue(
    UIValue* value
)
{
    this->value = value;
}



UIValue* UIItem::getValue()
{
    return value;
}



bool UIItem::addChild(
    UIItem* item
)
{

    if(childrenCount >= MAX_CHILDREN)
        return false;


    children[childrenCount++] = item;


    item->setParent(this);


    return true;
}



UIItem* UIItem::child(
    uint8_t index
)
{

    if(index >= childrenCount)
        return nullptr;


    return children[index];
}



uint8_t UIItem::childCount() const
{
    return childrenCount;
}



void UIItem::setParent(
    UIItem* parent
)
{
    parentItem = parent;
}



UIItem* UIItem::parent()
{
    return parentItem;
}



void UIItem::execute()
{

    if(callback)
    {
        callback(this);
    }

}



void UIItem::setCallback(
    UICallback callback
)
{
    this->callback = callback;
}



const char* UIItem::title() const
{
    return itemTitle;
}



UIItemType UIItem::type() const
{
    return itemType;
}



bool UIItem::hasChildren() const
{
    return childrenCount > 0;
}



bool UIItem::isVisible()
{

    if(visibilityCallback)
        return visibilityCallback();


    return true;
}



bool UIItem::isEnabled()
{

    if(enabledCallback)
        return enabledCallback();


    return true;
}



void UIItem::setVisibilityCallback(
    UIVisibilityCallback callback
)
{
    visibilityCallback = callback;
}



void UIItem::setEnabledCallback(
    UIVisibilityCallback callback
)
{
    enabledCallback = callback;
}


}