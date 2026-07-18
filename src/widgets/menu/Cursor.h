#ifndef EMBEDDED_UI_CURSOR_H
#define EMBEDDED_UI_CURSOR_H


#include "Node.h"


namespace EmbeddedUI
{


class Cursor
{

public:


    Cursor();



    /**
     * @brief Define o nó inicial da navegação.
     */
    void attach(
        Node* root
    );



    /**
     * @brief Retorna o nó atualmente selecionado.
     */
    Node* current() const;



    /**
     * @brief Move para próximo irmão.
     */
    bool moveNext();



    /**
     * @brief Move para irmão anterior.
     */
    bool movePrevious();



    /**
     * @brief Entra no primeiro filho.
     */
    bool enter();



    /**
     * @brief Retorna ao nó pai.
     */
    bool back();



    /**
     * @brief Retorna posição do cursor entre irmãos.
     *
     * Exemplo:
     *
     * Item 0
     * Item 1
     * Item 2 <- retorna 2
     */
    uint16_t index() const;



    /**
     * @brief Retorna quantidade de itens
     * no mesmo nível.
     */
    uint16_t siblingCount() const;



private:


    Node* _current;


};


}


#endif