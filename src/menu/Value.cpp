#include "Value.h"


namespace EmbeddedUI
{


UIValue::UIValue(
    UIValueType type
)
:
valueType(type)
{

}



UIValue::~UIValue()
{

}



void UIValue::beginEdit()
{

}



void UIValue::commit()
{

}



void UIValue::cancel()
{

}



void UIValue::increase()
{

}



void UIValue::decrease()
{

}



const char* UIValue::text()
{
    return "";
}



UIValueType UIValue::type() const
{
    return valueType;
}





UIIntValue::UIIntValue(
    int* value,
    int minimum,
    int maximum,
    int step
)
:
UIValue(UIValueType::INTEGER),
value(value),
backup(0),
minimum(minimum),
maximum(maximum),
step(step)
{

}



void UIIntValue::beginEdit()
{
    backup = *value;
}



void UIIntValue::commit()
{

}



void UIIntValue::cancel()
{
    *value = backup;
}



void UIIntValue::increase()
{

    if((*value + step) <= maximum)
        *value += step;

}



void UIIntValue::decrease()
{

    if((*value - step) >= minimum)
        *value -= step;

}



const char* UIIntValue::text()
{
    snprintf(
        buffer,
        sizeof(buffer),
        "%d",
        *value
    );

    return buffer;
}





UIFloatValue::UIFloatValue(
    float* value,
    float minimum,
    float maximum,
    float step
)
:
UIValue(UIValueType::FLOAT),
value(value),
backup(0),
minimum(minimum),
maximum(maximum),
step(step)
{

}



void UIFloatValue::beginEdit()
{
    backup = *value;
}



void UIFloatValue::commit()
{

}



void UIFloatValue::cancel()
{
    *value = backup;
}



void UIFloatValue::increase()
{

    if((*value + step) <= maximum)
        *value += step;

}



void UIFloatValue::decrease()
{

    if((*value - step) >= minimum)
        *value -= step;

}



const char* UIFloatValue::text()
{
    snprintf(
        buffer,
        sizeof(buffer),
        "%.2f",
        *value
    );

    return buffer;
}





UIBoolValue::UIBoolValue(
    bool* value
)
:
UIValue(UIValueType::BOOLEAN),
value(value),
backup(false)
{

}



void UIBoolValue::beginEdit()
{
    backup = *value;
}



void UIBoolValue::commit()
{

}



void UIBoolValue::cancel()
{
    *value = backup;
}



void UIBoolValue::increase()
{
    *value = !(*value);
}



void UIBoolValue::decrease()
{
    *value = !(*value);
}



const char* UIBoolValue::text()
{
    return *value ? "ON" : "OFF";
}





UIListValue::UIListValue(
    uint8_t* value,
    const char* const* items,
    uint8_t count
)
:
UIValue(UIValueType::LIST),
value(value),
backup(0),
items(items),
count(count)
{

}



void UIListValue::beginEdit()
{
    backup = *value;
}



void UIListValue::commit()
{

}



void UIListValue::cancel()
{
    *value = backup;
}



void UIListValue::increase()
{

    if((*value + 1) < count)
        (*value)++;

}



void UIListValue::decrease()
{

    if(*value > 0)
        (*value)--;

}



const char* UIListValue::text()
{
    return items[*value];
}


}