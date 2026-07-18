#ifndef EMBEDDED_UI_RENDERER_H
#define EMBEDDED_UI_RENDERER_H


#include "../drivers/display/DisplayDriver.h"

#include "../theme/Theme.h"

#include "../font/Font.h"


#include "Layout.h"
#include "ScrollManager.h"


#include "../widgets/menu/Menu.h"
#include "../widgets/menu/Cursor.h"
#include "../widgets/menu/InteractionState.h"



namespace EmbeddedUI
{


class Renderer
{

public:


    Renderer(
        UIDisplayDriver& display,
        Theme& theme,
        Font& font
    );



    void begin();



    /**
     * @brief Renderiza menu atual.
     */
    void render(
        Menu& menu,
        Cursor& cursor,
        InteractionState& state
    );



private:


    UIDisplayDriver& _display;


    Theme& _theme;


    Font& _font;



    Layout _layout;


    ScrollManager _scroll;



    void drawNode(
        Node* node,
        uint8_t line,
        bool selected
    );



    void drawValue(
        ValueNode* value,
        uint16_t x,
        uint16_t y
    );


};


}


#endif