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
     * @brief Move para o próximo irmão.
     */
    bool moveNext();



    /**
     * @brief Move para o irmão anterior.
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
     * @brief Retorna a posição do cursor
     * entre os irmãos.
     */
    uint16_t index() const;



    /**
     * @brief Retorna a quantidade de nós
     * existentes no mesmo nível.
     */
    uint16_t siblingCount() const;



private:


    /**
     * @brief Retorna o primeiro nó
     * do nível atual.
     */
    Node* firstSibling() const;



    Node* _current;


};


}


#endif