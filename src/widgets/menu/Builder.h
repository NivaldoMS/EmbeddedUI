#ifndef EMBEDDEDUI_BUILDER_H
#define EMBEDDEDUI_BUILDER_H


#include "Menu.h"
#include "ValueNode.h"
#include "ListNode.h"


namespace EmbeddedUI
{


/**
 * @brief Auxilia na montagem e configuração da árvore do menu.
 *
 * O Builder não cria, não destrói e não assume
 * propriedade sobre os nós.
 *
 * Os nós devem ser criados e mantidos pelo usuário.
 */
class Builder
{

public:


    explicit Builder(
        Menu& menu
    );



    /**
     * @brief Reinicia o Builder na raiz do menu.
     *
     * Quando clearTree for true, remove os vínculos
     * da árvore construída anteriormente.
     */
    Builder& begin(
        bool clearTree = true
    );



    /**
     * @brief Adiciona uma pasta previamente configurada
     * e passa a inserir os próximos nós dentro dela.
     */
    Builder& folder(
        Node& node
    );


    /**
     * @brief Configura e adiciona uma pasta.
     */
    Builder& folder(
        Node& node,
        const char* caption
    );



    /**
     * @brief Adiciona um ValueNode previamente configurado.
     */
    Builder& value(
        ValueNode& node
    );



    /**
     * @brief Configura e adiciona um valor inteiro.
     */
    Builder& integer(
        ValueNode& node,
        const char* caption,
        float minimum,
        float maximum,
        float step,
        float initialValue
    );



    /**
     * @brief Configura e adiciona um valor float.
     */
    Builder& floating(
        ValueNode& node,
        const char* caption,
        float minimum,
        float maximum,
        float step,
        float initialValue
    );



    /**
     * @brief Configura e adiciona um valor booleano.
     */
    Builder& boolean(
        ValueNode& node,
        const char* caption,
        bool initialValue
    );

    template<typename... Options>
    Builder& list(
        ListNode& node,
        const char* caption,
        uint8_t initialIndex,
        Options... options
    )
    {

        node.configure(
            caption
        );


        addListOptions(
            node,
            options...
        );


        node.setSelectedIndex(
            initialIndex
        );


        value(
            node
        );


        return *this;

    }

    /**
     * @brief Adiciona uma ação previamente configurada.
     */
    Builder& action(
        Node& node
    );


    /**
     * @brief Configura e adiciona uma ação.
     */
    Builder& action(
        Node& node,
        const char* caption
    );



    /**
     * @brief Adiciona um separador previamente configurado.
     */
    Builder& separator(
        Node& node
    );



    /**
     * @brief Retorna ao nível pai.
     */
    Builder& end();



    /**
     * @brief Retorna o nó atualmente usado
     * como contêiner pelo Builder.
     */
    Node* current() const;



private:


    bool append(
        Node& node
    );

    void addListOptions(
        ListNode&
    )
    {

    }


    template<typename... Remaining>
    void addListOptions(
        ListNode& node,
        const char* option,
        Remaining... remaining
    )
    {

        node.addOption(
            option
        );


        addListOptions(
            node,
            remaining...
        );

    }

    Menu& _menu;


    Node* _current;


};


}


#endif