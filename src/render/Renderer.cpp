#include "Renderer.h"

#include <stdio.h>


namespace EmbeddedUI
{


Renderer::Renderer(
    DisplayDriver& display,
    Theme& theme,
    Font& font
)
:
_display(display),
_theme(theme),
_font(font),
_background(),
_layout(theme),
_scroll()
{

}



void Renderer::begin()
{

    _display.begin();



    if(_font.valid())
    {
        _display.setFont(
            _font
        );
    }



    _background.setBitmap(
        _theme.background
    );



    configureLayout();

}



void Renderer::configureLayout()
{

    uint8_t visibleLines =
        1;



    if(_theme.lineHeight > 0)
    {

        const uint16_t top =
            _theme.marginTop >= _theme.lineHeight
            ?
            _theme.marginTop - _theme.lineHeight
            :
            0;



        const uint16_t availableHeight =
            _display.height() > top
            ?
            _display.height() - top
            :
            0;



        visibleLines =
            static_cast<uint8_t>(
                availableHeight /
                _theme.lineHeight
            );



        if(visibleLines == 0)
        {
            visibleLines = 1;
        }

    }



    _scroll.configure(
        visibleLines
    );

}



void Renderer::render(
    Menu& menu,
    Cursor& cursor,
    InteractionState& state
)
{

    (void)menu;



    _display.clear();



    _display.setDrawColor(
        _theme.backgroundColor
    );



    /*
     * A limpeza do buffer já define o estado
     * inicial do fundo em displays monocromáticos.
     */

    _display.setDrawColor(
        _theme.textColor
    );



    _background.setBitmap(
        _theme.background
    );



    _background.draw(
        _display
    );



    Node* current =
        cursor.current();



    if(!current)
    {

        _display.refresh();

        return;

    }



    Node* first =
        current;



    while(
        first->previousSibling()
    )
    {

        first =
            first->previousSibling();

    }



    const uint16_t selectedIndex =
        cursor.index();



    const uint16_t totalItems =
        cursor.siblingCount();



    _scroll.update(
        selectedIndex,
        totalItems
    );



    Node* item =
        first;



    const uint16_t skip =
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



    uint8_t line =
        0;



    while(
        item &&
        line < _scroll.visibleLines()
    )
    {

        if(item->isVisible())
        {

            drawNode(
                item,
                line,
                item == current,
                state.editing() &&
                state.valueNode() == item
            );



            line++;

        }



        item =
            item->nextSibling();

    }



    _display.refresh();

}



DisplayDriver& Renderer::display()
{

    return _display;

}



Theme& Renderer::theme()
{

    return _theme;

}



Font& Renderer::font()
{

    return _font;

}



void Renderer::drawNode(
    Node* node,
    uint8_t line,
    bool selected,
    bool editing
)
{

    if(!node)
        return;



    const int16_t y =
        _layout.lineY(
            line
        );



    if(selected)
    {

        const Rect rect =
            _layout.itemRect(
                line,
                _display.width()
            );



        _display.setDrawColor(
            _theme.selectedColor
        );



        _display.fillRect(
            rect.x,
            rect.y,
            rect.width,
            rect.height
        );



        _display.setDrawColor(
            _theme.selectedTextColor
        );

    }
    else
    {

        _display.setDrawColor(
            _theme.textColor
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



        if(editing)
        {

            const Rect valueArea =
                _layout.valueRect(
                    line,
                    _display.width()
                );



            /*
             * XOR permite exibir o contorno
             * tanto sobre fundo preenchido
             * quanto sobre fundo vazio.
             */
            _display.setDrawColor(
                2
            );



            _display.drawRect(
                valueArea.x,
                valueArea.y,
                valueArea.width,
                valueArea.height
            );

        }

    }



    _display.setDrawColor(
        _theme.textColor
    );

}



void Renderer::drawValue(
    ValueNode* value,
    int16_t x,
    int16_t y
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
                value->value() > 0.0f
                ?
                "ON"
                :
                "OFF"
            );

        break;



        default:

            buffer[0] =
                '\0';

        break;

    }



    _display.drawText(
        x,
        y,
        buffer
    );

}


}