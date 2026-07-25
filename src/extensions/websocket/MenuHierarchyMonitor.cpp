#include "MenuHierarchyMonitor.h"

#include <math.h>


namespace EmbeddedUI
{


MenuHierarchyMonitor::MenuHierarchyMonitor(
    WebSocketsServer& webSocket,
    Menu& menu
)
:
_webSocket(webSocket),
_menu(menu),
_selectedNode(nullptr),
_editingNode(nullptr),
_executingNode(nullptr),
_lastPayload(),
_forceUpdate(true)
{

}


void MenuHierarchyMonitor::setSelectedNode(
    Node* node
)
{

    if(
        _selectedNode ==
        node
    )
    {
        return;
    }


    _selectedNode =
        node;


    _forceUpdate =
        true;

}


void MenuHierarchyMonitor::setEditingNode(
    Node* node
)
{

    if(
        _editingNode ==
        node
    )
    {
        return;
    }


    _editingNode =
        node;


    _forceUpdate =
        true;

}


void MenuHierarchyMonitor::setExecutingNode(
    Node* node
)
{

    if(
        _executingNode ==
        node
    )
    {
        return;
    }


    _executingNode =
        node;


    _forceUpdate =
        true;

}


void MenuHierarchyMonitor::clearExecutingNode()
{

    setExecutingNode(
        nullptr
    );

}


void MenuHierarchyMonitor::forcePublish()
{

    _forceUpdate =
        true;

}


void MenuHierarchyMonitor::update()
{

    String payload =
        buildPayload();


    if(
        !_forceUpdate &&
        payload ==
            _lastPayload
    )
    {
        return;
    }


    _lastPayload =
        payload;


    _forceUpdate =
        false;


    _webSocket.broadcastTXT(
        _lastPayload
    );

}

void MenuHierarchyMonitor::sendCurrentState(
    uint8_t clientNumber
)
{

    String payload =
        buildPayload();


    _lastPayload =
        payload;


    _webSocket.sendTXT(
        clientNumber,
        payload
    );

}

String MenuHierarchyMonitor::buildPayload() const
{

    String output;


    output.reserve(
        1400
    );


    output +=
        F(
            "{"
            "\"type\":\"menuHierarchyMonitor\","
            "\"items\":["
        );


    Node* root =
        _menu.root();


    bool first =
        true;


    if(root)
    {

        Node* node =
            root->firstChild();


        while(node)
        {

            if(node->isVisible())
            {

                if(!first)
                {

                    output +=
                        ',';

                }


                appendNode(
                    output,
                    node
                );


                first =
                    false;

            }


            node =
                node->nextSibling();

        }

    }


    output +=
        F(
            "]"
            "}"
        );


    return output;

}


void MenuHierarchyMonitor::appendNode(
    String& output,
    Node* node
) const
{

    if(!node)
        return;


    output +=
        F(
            "{"
            "\"caption\":\""
        );


    appendEscapedJson(
        output,
        node->caption()
    );


    output +=
        F(
            "\","
            "\"nodeType\":\""
        );


    output +=
        nodeTypeName(
            node->type()
        );


    output +=
        F(
            "\","
            "\"enabled\":"
        );


    output +=
        node->isEnabled()
        ?
        F("true")
        :
        F("false");


    output +=
        F(
            ","
            "\"selected\":"
        );


    output +=
        node == _selectedNode
        ?
        F("true")
        :
        F("false");


    output +=
        F(
            ","
            "\"editing\":"
        );


    output +=
        node == _editingNode
        ?
        F("true")
        :
        F("false");


    output +=
        F(
            ","
            "\"executing\":"
        );


    output +=
        node == _executingNode
        ?
        F("true")
        :
        F("false");


    if(
        node->type() ==
        NodeType::Value
    )
    {

        output +=
            F(
                ","
                "\"value\":"
            );


        appendValue(
            output,
            static_cast<ValueNode*>(
                node
            )
        );

    }


    if(node->hasChildren())
    {

        output +=
            F(
                ","
                "\"children\":["
            );


        appendChildren(
            output,
            node
        );


        output +=
            ']';

    }


    output +=
        '}';

}


void MenuHierarchyMonitor::appendChildren(
    String& output,
    Node* parent
) const
{

    if(!parent)
        return;


    Node* child =
        parent->firstChild();


    bool first =
        true;


    while(child)
    {

        if(child->isVisible())
        {

            if(!first)
            {

                output +=
                    ',';

            }


            appendNode(
                output,
                child
            );


            first =
                false;

        }


        child =
            child->nextSibling();

    }

}


void MenuHierarchyMonitor::appendValue(
    String& output,
    ValueNode* valueNode
) const
{

    if(!valueNode)
    {

        output +=
            F("null");


        return;

    }


    switch(
        valueNode->valueType()
    )
    {

        case ValueType::Boolean:

            if(
                valueNode->value() >=
                0.5f
            )
            {

                output +=
                    F(
                        "{"
                        "\"type\":\"boolean\","
                        "\"raw\":true,"
                        "\"text\":\" On\""
                        "}"
                    );

            }
            else
            {

                output +=
                    F(
                        "{"
                        "\"type\":\"boolean\","
                        "\"raw\":false,"
                        "\"text\":\"Off\""
                        "}"
                    );

            }

        break;


        case ValueType::Integer:
        {

            const long value =
                static_cast<long>(
                    roundf(
                        valueNode->value()
                    )
                );


            output +=
                F(
                    "{"
                    "\"type\":\"integer\","
                    "\"raw\":"
                );


            output +=
                value;


            output +=
                F(
                    ","
                    "\"text\":\""
                );


            output +=
                value;


            output +=
                F(
                    "\""
                    "}"
                );

        }
        break;


        case ValueType::Float:
        default:
        {

            const String value(
                valueNode->value(),
                2
            );


            output +=
                F(
                    "{"
                    "\"type\":\"float\","
                    "\"raw\":"
                );


            output +=
                value;


            output +=
                F(
                    ","
                    "\"text\":\""
                );


            output +=
                value;


            output +=
                F(
                    "\""
                    "}"
                );

        }
        break;

    }

}


void MenuHierarchyMonitor::appendEscapedJson(
    String& output,
    const char* text
)
{

    if(!text)
        return;


    while(*text)
    {

        const char character =
            *text;


        switch(character)
        {

            case '"':

                output +=
                    F("\\\"");

            break;


            case '\\':

                output +=
                    F("\\\\");

            break;


            case '\n':

                output +=
                    F("\\n");

            break;


            case '\r':

                output +=
                    F("\\r");

            break;


            case '\t':

                output +=
                    F("\\t");

            break;


            default:

                if(
                    static_cast<uint8_t>(
                        character
                    ) >= 32
                )
                {

                    output +=
                        character;

                }

            break;

        }


        text++;

    }

}


const __FlashStringHelper*
MenuHierarchyMonitor::nodeTypeName(
    NodeType type
)
{

    switch(type)
    {

        case NodeType::Folder:

            return
                F("folder");


        case NodeType::Value:

            return
                F("value");


        case NodeType::Action:

            return
                F("action");


        case NodeType::Separator:

            return
                F("separator");


        default:

            return
                F("unknown");

    }

}


}