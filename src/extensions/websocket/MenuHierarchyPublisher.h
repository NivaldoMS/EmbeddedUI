#ifndef EMBEDDED_UI_MENU_HIERARCHY_PUBLISHER_H
#define EMBEDDED_UI_MENU_HIERARCHY_PUBLISHER_H


#include <Arduino.h>

#include <WebSocketsServer.h>

#include "../../widgets/menu/Menu.h"
#include "../../widgets/menu/Node.h"
#include "../../widgets/menu/ValueNode.h"


namespace EmbeddedUI
{


class MenuHierarchyPublisher
{

public:


    MenuHierarchyPublisher(
        WebSocketsServer& webSocket,
        Menu& menu
    );


    void update();


    void forcePublish();


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


    String _lastPayload;


    bool _forceUpdate;


};


}


#endif