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



/**
 * @brief Mantém o estado atual de interação
 * com o menu.
 *
 * Ao iniciar a edição, armazena o valor original.
 * A confirmação mantém o novo valor.
 * O cancelamento restaura o valor original.
 */
class InteractionState
{

public:


    InteractionState()
    :
    _mode(InteractionMode::Browse),
    _valueNode(nullptr),
    _originalValue(0.0f)
    {

    }



    /**
     * @brief Retorna o modo atual de interação.
     */
    InteractionMode mode() const
    {

        return _mode;

    }



    /**
     * @brief Inicia a edição de um ValueNode.
     *
     * O valor atual é armazenado para que
     * possa ser restaurado em caso de cancelamento.
     */
    void enterEdit(
        ValueNode* value
    )
    {

        if(!value)
            return;



        /*
         * Evita substituir o valor original
         * durante uma edição já iniciada.
         */
        if(editing())
            return;



        _valueNode =
            value;



        _originalValue =
            value->value();



        _mode =
            InteractionMode::Edit;

    }



    /**
     * @brief Confirma a edição.
     *
     * O novo valor permanece no ValueNode.
     */
    void confirmEdit()
    {

        if(!editing())
            return;



        clearEditState();

    }



    /**
     * @brief Cancela a edição.
     *
     * Restaura o valor que existia antes
     * do início da edição.
     */
    void cancelEdit()
    {

        if(!editing())
            return;



        if(_valueNode)
        {

            _valueNode->setValue(
                _originalValue
            );

        }



        clearEditState();

    }



    /**
     * @brief Encerra o modo de edição sem
     * alterar o valor atual.
     *
     * Mantido para operações internas e
     * compatibilidade com o código existente.
     */
    void leaveEdit()
    {

        clearEditState();

    }



    /**
     * @brief Informa se existe um valor em edição.
     */
    bool editing() const
    {

        return
            _mode == InteractionMode::Edit &&
            _valueNode != nullptr;

    }



    /**
     * @brief Retorna o ValueNode atualmente
     * em edição.
     */
    ValueNode* valueNode() const
    {

        return _valueNode;

    }



    /**
     * @brief Retorna o valor armazenado no
     * início da edição.
     */
    float originalValue() const
    {

        return _originalValue;

    }



private:


    void clearEditState()
    {

        _valueNode =
            nullptr;



        _originalValue =
            0.0f;



        _mode =
            InteractionMode::Browse;

    }



    InteractionMode _mode;


    ValueNode* _valueNode;


    float _originalValue;


};


}


#endif