#include "Render.h"

#include <stdio.h>


namespace EmbeddedUI
{


Render::Render(
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



void Render::begin()
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



void Render::configureLayout()
{

    uint8_t visibleLines =
        1;



    if(_theme.lineHeight > 0)
    {

        /*
         * marginTop representa a baseline
         * da primeira linha.
         *
         * Com:
         *
         * marginTop = 28
         * lineHeight = 12
         *
         * a área dos itens começa em y = 16.
         */
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

            visibleLines =
                1;

        }

    }



    _scroll.configure(
        visibleLines
    );

}



void Render::render(
    Menu& menu,
    Cursor& cursor,
    InteractionState& state
)
{

    _display.beginFrame();



    do
    {

        drawPage(
            menu,
            cursor,
            state
        );

    }
    while(_display.nextFrame());

}



void Render::drawHeader(
    Menu& menu,
    Cursor& cursor
)
{

    const char* title =
        "Menu";



    Node* root =
        menu.root();



    Node* current =
        cursor.current();



    if(
        root != nullptr &&
        current != nullptr
    )
    {

        Node* parent =
            current->parent();



        /*
         * Quando o item selecionado pertence
         * diretamente à raiz, o título é "Menu".
         *
         * Quando pertence a um submenu, utiliza
         * o título desse submenu.
         */
        if(
            parent != nullptr &&
            parent != root
        )
        {

            const char* parentCaption =
                parent->caption();



            if(
                parentCaption != nullptr &&
                parentCaption[0] != '\0'
            )
            {

                title =
                    parentCaption;

            }

        }

    }



    _display.setDrawColor(
        _theme.textColor
    );



    /*
     * Baseline em y = 12.
     *
     * O texto permanece dentro da faixa
     * amarela de 0 até 15 pixels.
     */
    _display.drawText(
        _theme.marginLeft,
        12,
        title
    );



    /*
     * Linha divisória no último pixel
     * da faixa superior.
     */
    _display.drawRect(
        0,
        15,
        _display.width(),
        1
    );

}



void Render::drawPage(
    Menu& menu,
    Cursor& cursor,
    InteractionState& state
)
{

    _display.setDrawColor(
        _theme.textColor
    );



    _background.setBitmap(
        _theme.background
    );



    _background.draw(
        _display
    );



    drawHeader(
        menu,
        cursor
    );



    Node* current =
        cursor.current();



    if(!current)
    {

        return;

    }



    Node* first =
        current;



    while(first->previousSibling())
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
        uint16_t index = 0;
        index < skip && item;
        index++
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

}



DisplayDriver& Render::display()
{

    return
        _display;

}



Theme& Render::theme()
{

    return
        _theme;

}



Font& Render::font()
{

    return
        _font;

}



void Render::drawNode(
    Node* node,
    uint8_t line,
    bool selected,
    bool editing
)
{

    if(!node)
    {

        return;

    }



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



    const char* caption =
        node->caption();



    _display.drawText(
        _theme.marginLeft,
        y,
        caption != nullptr
        ?
        caption
        :
        ""
    );



    if(
        node->type() ==
        NodeType::Value
    )
    {

        drawValue(
            static_cast<ValueNode*>(
                node
            ),
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
             * No U8g2, draw color 2 utiliza
             * normalmente o modo XOR.
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



void Render::drawValue(
    ValueNode* value,
    int16_t x,
    int16_t y
)
{

    if(!value)
    {

        return;

    }



    char buffer[
        24
    ];



    buffer[0] =
        '\0';



    const char* text =
        buffer;



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



        case ValueType::List:
        {

            ListNode* listNode =
                static_cast<ListNode*>(
                    value
                );



            text =
                listNode->selectedText();



            if(text == nullptr)
            {

                text =
                    "";

            }

        }
        break;



        default:

            text =
                "";

        break;

    }



    _display.drawText(
        x,
        y,
        text
    );

}


}