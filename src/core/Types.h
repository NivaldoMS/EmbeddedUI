#ifndef EMBEDDED_UI_TYPES_H
#define EMBEDDED_UI_TYPES_H


#include <Arduino.h>


namespace EmbeddedUI
{


/**
 * @brief Estado visual ou lógico genérico
 * de um componente.
 */
enum class State : uint8_t
{

    NORMAL = 0,


    ACTIVE,


    EDITING

};



/**
 * @brief Tipos genéricos de componentes.
 */
enum class ComponentType : uint8_t
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
 * @brief Tipos genéricos de itens.
 *
 * Mantido para componentes que não utilizam
 * diretamente NodeType e ValueType.
 */
enum class ItemType : uint8_t
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
 * @brief Resultado de uma operação
 * ou processamento de evento.
 */
enum class Result : uint8_t
{

    NONE = 0,


    /**
     * O evento ou operação não foi tratado.
     */
    IGNORED,


    /**
     * O evento foi tratado.
     */
    HANDLED,


    /**
     * A operação foi cancelada.
     */
    CANCELLED,


    /**
     * A operação alterou algum estado.
     */
    CHANGED,


    /**
     * Ocorreu um erro.
     */
    ERROR

};



/**
 * @brief Direção genérica de navegação.
 */
enum class Direction : int8_t
{

    NONE = 0,


    UP = -1,


    DOWN = 1

};


}


#endif