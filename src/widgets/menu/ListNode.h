#ifndef EMBEDDEDUI_LIST_NODE_H
#define EMBEDDEDUI_LIST_NODE_H


#include "ValueNode.h"


namespace EmbeddedUI
{


class ListNode : public ValueNode
{

public:


    static constexpr uint8_t MaximumOptions =
        16;



    explicit ListNode(
        const char* caption = nullptr
    );



    void configure(
        const char* caption
    );



    void clearOptions();



    bool addOption(
        const char* text
    );



    uint8_t optionCount() const;



    const char* option(
        uint8_t index
    ) const;



    uint8_t selectedIndex() const;



    const char* selectedText() const;



    bool setSelectedIndex(
        uint8_t index
    );



private:


    const char* _options[
        MaximumOptions
    ];


    uint8_t _optionCount;


};


}


#endif