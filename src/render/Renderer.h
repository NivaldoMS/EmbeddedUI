#ifndef EMBEDDED_UI_RENDERER_H
#define EMBEDDED_UI_RENDERER_H


#include "../drivers/display/DisplayDriver.h"

#include "../theme/Theme.h"

#include "../font/Font.h"

#include "../widgets/menu/Menu.h"

#include "../widgets/menu/Cursor.h"

#include "../widgets/menu/InteractionState.h"

#include "../widgets/menu/ValueNode.h"

#include "Background.h"

#include "Layout.h"

#include "ScrollManager.h"


namespace EmbeddedUI
{


class Renderer
{

public:


    Renderer(
        DisplayDriver& display,
        Theme& theme,
        Font& font
    );



    /**
     * @brief Inicializa o renderizador.
     */
    void begin();



    /**
     * @brief Renderiza um menu.
     */
    void render(
        Menu& menu,
        Cursor& cursor,
        InteractionState& state
    );



    DisplayDriver& display();



    Theme& theme();



    Font& font();



private:


    void configureLayout();



    void drawPage(
        Menu& menu,
        Cursor& cursor,
        InteractionState& state
    );



    void drawNode(
        Node* node,
        uint8_t line,
        bool selected,
        bool editing
    );



    void drawValue(
        ValueNode* value,
        int16_t x,
        int16_t y
    );



    DisplayDriver& _display;


    Theme& _theme;


    Font& _font;


    Background _background;


    Layout _layout;


    ScrollManager _scroll;


};


}


#endif