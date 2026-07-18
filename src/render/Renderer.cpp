#include "Renderer.h"

#include "../widgets/menu/ValueNode.h"


namespace EmbeddedUI
{


Renderer::Renderer(
    UIDisplayDriver& display,
    Theme& theme,
    Font& font
)
:
_display(display),
_theme(theme),
_font(font),
_layout(theme),
_scroll()
{

}



void Renderer::begin()
{

    _display.begin();

}



void Renderer::render(
    Menu& menu,
    Cursor& cursor,
    InteractionState& state
)
{

    _display.clear();



    Node* current =
        cursor.current();



    if(!current)
    {
        _display.refresh();
        return;
    }



    Node* parent =
        current;



    if(current->parent())
    {
        parent =
            current->parent();
    }



    uint16_t selectedIndex =
        cursor.index();



    uint16_t totalItems =
        cursor.siblingCount();



    _scroll.update(
        selectedIndex,
        totalItems
    );



    Node* item =
        parent->firstChild();



    uint16_t skip =
        _scroll.firstVisible();



    for(
        uint16_t i = 0;
        i < skip && item;
        i++
    )
    {
        item =
            item->nextSibling();
    }



    uint8_t line = 0;



    while(
        item &&
        line < _scroll.visibleLines()
    )
    {


        drawNode(
            item,
            line,
            item == current
        );



        item =
            item->nextSibling();



        line++;

    }



    _display.refresh();

}



void Renderer::drawNode(
    Node* node,
    uint8_t line,
    bool selected
)
{

    if(!node)
        return;



    uint16_t y =
        _layout.lineY(
            line
        );



    if(selected)
    {

        Rect rect =
            _layout.itemRect(
                line,
                _display.width()
            );


        _display.fillRect(
            rect.x,
            rect.y,
            rect.width,
            rect.height
        );

    }



    _display.drawText(
        _theme.marginLeft,
        y,
        node->caption()
    );



    if(node->type() == NodeType::Value)
    {

        drawValue(
            static_cast<ValueNode*>(node),
            _layout.valueX(
                _display.width()
            ),
            y
        );

    }

}



void Renderer::drawValue(
    ValueNode* value,
    uint16_t x,
    uint16_t y
)
{

    if(!value)
        return;



    char buffer[16];



    switch(value->valueType())
    {


        case ValueType::Integer:

            snprintf(
                buffer,
                sizeof(buffer),
                "%.0f",
                value->value()
            );

        break;



        case ValueType::Float:

            snprintf(
                buffer,
                sizeof(buffer),
                "%.2f",
                value->value()
            );

        break;



        case ValueType::Boolean:

            snprintf(
                buffer,
                sizeof(buffer),
                "%s",
                value->value() > 0
                ?
                "ON"
                :
                "OFF"
            );

        break;


    }



    _display.drawText(
        x,
        y,
        buffer
    );

}


}