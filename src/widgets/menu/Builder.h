#ifndef EMBEDDEDUI_BUILDER_H
#define EMBEDDEDUI_BUILDER_H


#include "Menu.h"
#include "ValueNode.h"


namespace EmbeddedUI
{


/**
 * @brief Auxilia na montagem da árvore do menu.
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
     * @brief Adiciona uma pasta e passa a inserir
     * os próximos nós dentro dela.
     */
    Builder& folder(
        Node& node
    );



    /**
     * @brief Adiciona um nó de valor ao nível atual.
     */
    Builder& value(
        ValueNode& node
    );



    /**
     * @brief Adiciona um nó de ação ao nível atual.
     */
    Builder& action(
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


    Menu& _menu;


    Node* _current;


};


}


#endif