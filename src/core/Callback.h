#ifndef EMBEDDED_UI_CALLBACK_H
#define EMBEDDED_UI_CALLBACK_H


namespace EmbeddedUI
{


/**
 * @brief Callback usado para determinar
 * dinamicamente a visibilidade de um componente.
 */
using VisibilityCallback =
    bool (*)();


}


#endif