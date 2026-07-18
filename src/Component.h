#ifndef EMBEDDED_UI_COMPONENT_H
#define EMBEDDED_UI_COMPONENT_H


#include <Arduino.h>

#include "Types.h"
#include "Callback.h"


namespace EmbeddedUI
{


/**
 * @brief Classe base de todos os elementos visuais da biblioteca.
 *
 * Componentes possuem:
 * - tipo
 * - estado
 * - visibilidade
 * - ciclo de atualização
 */
class UIComponent
{

public:


    UIComponent(
        UIComponentType componentType = UIComponentType::NONE
    );


    virtual ~UIComponent();


    /**
     * @brief Inicialização do componente.
     */
    virtual void begin();


    /**
     * @brief Atualização periódica.
     */
    virtual void update();


    /**
     * @brief Recebe eventos da interface.
     */
    virtual UIResult handleEvent(
        const UIEvent& event
    );


    /**
     * @brief Retorna o tipo do componente.
     */
    UIComponentType type() const;


    /**
     * @brief Define visibilidade.
     */
    void setVisible(
        bool state
    );


    /**
     * @brief Verifica visibilidade.
     */
    bool isVisible() const;


    /**
     * @brief Define callback de visibilidade dinâmica.
     */
    void setVisibilityCallback(
        UIVisibilityCallback callback
    );


protected:


    UIComponentType componentType;


    UIState state;


    bool visible;


    UIVisibilityCallback visibilityCallback;


};


}


#endif