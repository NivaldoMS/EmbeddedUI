#ifndef EMBEDDED_UI_ITEM_H
#define EMBEDDED_UI_ITEM_H


#include <Arduino.h>

#include "../core/Types.h"
#include "../core/Callback.h"
#include "Value.h"


namespace EmbeddedUI
{


/**
 * @brief Representa um item dentro de uma tela de menu.
 */
class UIItem
{

public:


    UIItem(
        const char* title,
        UIItemType type = UIItemType::NONE
    );


    virtual ~UIItem();



    /**
     * @brief Define valor associado ao item.
     */
    void setValue(
        UIValue* value
    );



    /**
     * @brief Retorna valor associado.
     */
    UIValue* getValue();



    /**
     * @brief Adiciona item filho.
     */
    bool addChild(
        UIItem* item
    );



    /**
     * @brief Retorna filho pelo índice.
     */
    UIItem* child(
        uint8_t index
    );



    /**
     * @brief Quantidade de filhos.
     */
    uint8_t childCount() const;



    /**
     * @brief Define item pai.
     */
    void setParent(
        UIItem* parent
    );



    /**
     * @brief Retorna item pai.
     */
    UIItem* parent();



    /**
     * @brief Executa ação associada.
     */
    void execute();



    /**
     * @brief Define callback.
     */
    void setCallback(
        UICallback callback
    );



    /**
     * @brief Retorna título.
     */
    const char* title() const;



    /**
     * @brief Tipo do item.
     */
    UIItemType type() const;



    /**
     * @brief Verifica se possui filhos.
     */
    bool hasChildren() const;



    /**
     * @brief Controle de visibilidade.
     */
    bool isVisible();



    /**
     * @brief Controle de habilitação.
     */
    bool isEnabled();



    void setVisibilityCallback(
        UIVisibilityCallback callback
    );


    void setEnabledCallback(
        UIVisibilityCallback callback
    );



private:


    static constexpr uint8_t MAX_CHILDREN = 16;


    const char* itemTitle;


    UIItemType itemType;


    UIValue* value;


    UIItem* parentItem;


    UIItem* children[MAX_CHILDREN];


    uint8_t childrenCount;


    UICallback callback;


    UIVisibilityCallback visibilityCallback;


    UIVisibilityCallback enabledCallback;


};


}


#endif