#ifndef EMBEDDED_UI_CALLBACK_H
#define EMBEDDED_UI_CALLBACK_H


namespace EmbeddedUI
{


class UIComponent;


/**
 * @brief Callback genérico da interface.
 */
typedef void (*UICallback)(UIComponent*);


/**
 * @brief Callback que permite controlar visibilidade.
 */
typedef bool (*UIVisibilityCallback)();


/**
 * @brief Callback de validação.
 */
typedef bool (*UIValidationCallback)();


}


#endif