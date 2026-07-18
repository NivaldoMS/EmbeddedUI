#ifndef EMBEDDED_UI_COMPONENT_H
#define EMBEDDED_UI_COMPONENT_H


#include <Arduino.h>

#include "Types.h"
#include "Event.h"
#include "Callback.h"


namespace EmbeddedUI
{


/**
 * @brief Classe base dos componentes visuais.
 */
class Component
{

public:


    explicit Component(
        ComponentType componentType =
            ComponentType::NONE
    );



    virtual ~Component();



    /**
     * @brief Inicializa o componente.
     */
    virtual void begin();



    /**
     * @brief Atualiza o componente.
     */
    virtual void update();



    /**
     * @brief Processa um evento.
     */
    virtual Result handleEvent(
        const Event& event
    );



    /**
     * @brief Retorna o tipo do componente.
     */
    ComponentType type() const;



    /**
     * @brief Define a visibilidade fixa.
     */
    void setVisible(
        bool visible
    );



    /**
     * @brief Retorna a visibilidade atual.
     *
     * Quando existir um callback, seu retorno
     * terá prioridade sobre o valor fixo.
     */
    bool isVisible() const;



    /**
     * @brief Define um callback dinâmico
     * de visibilidade.
     */
    void setVisibilityCallback(
        VisibilityCallback callback
    );



protected:


    ComponentType componentType;


    State state;


    bool visible;


    VisibilityCallback visibilityCallback;


};


}


#endif