#ifndef EMBEDDED_UI_TYPES_H
#define EMBEDDED_UI_TYPES_H


#include <Arduino.h>


namespace EmbeddedUI
{


/**
 * @brief Estados gerais da interface.
 */
enum class UIState : uint8_t
{
    NORMAL = 0,
    ACTIVE,
    EDITING
};


/**
 * @brief Tipo de componente.
 */
enum class UIComponentType : uint8_t
{
    NONE = 0,

    SCREEN,

    MENU,

    ITEM,

    VALUE,

    DIALOG,

    POPUP
};


/**
 * @brief Tipo de item de menu.
 */
enum class UIItemType : uint8_t
{
    NONE = 0,

    SUBMENU,

    INTEGER,

    FLOAT,

    BOOLEAN,

    LIST,

    ACTION
};


/**
 * @brief Resultado de uma ação da interface.
 */
enum class UIResult : uint8_t
{
    NONE = 0,

    HANDLED,

    CANCELLED,

    CHANGED,

    ERROR
};


/**
 * @brief Direções de navegação.
 */
enum class UIDirection : int8_t
{
    NONE = 0,

    UP = -1,

    DOWN = 1
};


}


#endif