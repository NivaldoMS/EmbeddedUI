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


    InteractionState()
    :
    _mode(InteractionMode::Browse),
    _valueNode(nullptr)
    {

    }



    /**
     * @brief Retorna o modo atual.
     */
    InteractionMode mode() const
    {

        return _mode;

    }



    /**
     * @brief Inicia a edição de um ValueNode.
     */
    void enterEdit(
        ValueNode* value
    )
    {

        if(!value)
            return;



        _valueNode =
            value;



        _mode =
            InteractionMode::Edit;

    }



    /**
     * @brief Finaliza o modo de edição.
     */
    void leaveEdit()
    {

        _valueNode =
            nullptr;



        _mode =
            InteractionMode::Browse;

    }



    /**
     * @brief Informa se está no modo de edição.
     */
    bool editing() const
    {

        return
            _mode == InteractionMode::Edit;

    }



    /**
     * @brief Retorna o ValueNode em edição.
     */
    ValueNode* valueNode() const
    {

        return _valueNode;

    }



private:


    InteractionMode _mode;


    ValueNode* _valueNode;


};


}


#endif