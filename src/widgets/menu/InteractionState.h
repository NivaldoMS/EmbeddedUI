#ifndef EMBEDDED_UI_INTERACTION_STATE_H
#define EMBEDDED_UI_INTERACTION_STATE_H


#include <Arduino.h>

#include "ValueNode.h"


namespace EmbeddedUI
{


enum class InteractionMode : uint8_t
{
    Browse = 0,
    Edit
};



class InteractionState
{

public:


    InteractionState();



    /**
     * @brief Retorna o modo atual de interação.
     */
    InteractionMode mode() const;



    /**
     * @brief Inicia a edição de um valor.
     */
    void enterEdit(
        ValueNode* value
    );



    /**
     * @brief Finaliza o modo de edição.
     */
    void leaveEdit();



    /**
     * @brief Informa se existe um valor em edição.
     */
    bool editing() const;



    /**
     * @brief Retorna o ValueNode atualmente
     * associado ao modo de edição.
     */
    ValueNode* valueNode() const;



private:


    InteractionMode _mode;


    ValueNode* _valueNode;


};


}


#endif