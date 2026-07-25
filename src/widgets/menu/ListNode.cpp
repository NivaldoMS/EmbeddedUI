#include "ListNode.h"


namespace EmbeddedUI
{


ListNode::ListNode(
    const char* caption
)
:
ValueNode(
    caption,
    ValueType::List
),
_options(),
_optionCount(0)
{

}



void ListNode::configure(
    const char* caption
)
{

    ValueNode::configure(
        caption,
        ValueType::List
    );


    clearOptions();

}



void ListNode::clearOptions()
{

    for(
        uint8_t index = 0;
        index < MaximumOptions;
        index++
    )
    {

        _options[index] =
            nullptr;

    }


    _optionCount =
        0;


    setRange(
        0.0f,
        0.0f,
        1.0f
    );


    setValue(
        0.0f
    );

}



bool ListNode::addOption(
    const char* text
)
{

    if(text == nullptr)
    {

        return false;

    }


    if(_optionCount >= MaximumOptions)
    {

        return false;

    }


    _options[
        _optionCount
    ] = text;


    _optionCount++;


    setRange(
        0.0f,
        static_cast<float>(
            _optionCount - 1
        ),
        1.0f
    );


    return true;

}



uint8_t ListNode::optionCount() const
{

    return
        _optionCount;

}



const char* ListNode::option(
    uint8_t index
) const
{

    if(index >= _optionCount)
    {

        return nullptr;

    }


    return
        _options[index];

}



uint8_t ListNode::selectedIndex() const
{

    return static_cast<uint8_t>(
        value()
    );

}



const char* ListNode::selectedText() const
{

    const char* text =
        option(
            selectedIndex()
        );


    return
        text != nullptr
        ?
        text
        :
        "";

}



bool ListNode::setSelectedIndex(
    uint8_t index
)
{

    if(index >= _optionCount)
    {

        return false;

    }


    setValue(
        static_cast<float>(
            index
        )
    );


    return true;

}


}