#ifndef EMBEDDED_UI_MENU_HIERARCHY_MONITOR_H
#define EMBEDDED_UI_MENU_HIERARCHY_MONITOR_H


#include <Arduino.h>

#include <WebSocketsServer.h>

#include "../../widgets/menu/Menu.h"
#include "../../widgets/menu/Node.h"
#include "../../widgets/menu/ValueNode.h"
#include "../../widgets/menu/ListNode.h"


namespace EmbeddedUI
{


class MenuHierarchyMonitor
{

public:


    MenuHierarchyMonitor(
        WebSocketsServer& webSocket,
        Menu& menu
    );


    /**
     * @brief Define o item atualmente selecionado.
     */
    void setSelectedNode(
        Node* node
    );


    /**
     * @brief Define o item atualmente em edição.
     */
    void setEditingNode(
        Node* node
    );


    /**
     * @brief Define a ação atualmente em execução.
     */
    void setExecutingNode(
        Node* node
    );


    /**
     * @brief Limpa o estado de execução.
     */
    void clearExecutingNode();


    /**
     * @brief Força a próxima publicação.
     */
    void forcePublish();


    /**
     * @brief Compara o estado atual com o anterior
     * e transmite somente quando houver alteração.
     */
    void update();


    /**
     * @brief Envia o estado atual para um cliente.
     */
    void sendCurrentState(
        uint8_t clientNumber
    );


private:


    void appendNode(
        String& output,
        Node* node
    ) const;


    void appendChildren(
        String& output,
        Node* parent
    ) const;


    void appendValue(
        String& output,
        ValueNode* valueNode
    ) const;


    static void appendEscapedJson(
        String& output,
        const char* text
    );


    static const __FlashStringHelper* nodeTypeName(
        NodeType type
    );


    String buildPayload() const;


    WebSocketsServer& _webSocket;


    Menu& _menu;


    Node* _selectedNode;


    Node* _editingNode;


    Node* _executingNode;


    String _lastPayload;


    bool _forceUpdate;


};


}


#endif