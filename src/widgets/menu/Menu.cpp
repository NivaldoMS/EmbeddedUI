#include "Menu.h"


namespace EmbeddedUI
{


Menu::Menu()
:
_root(
    "Root",
    NodeType::Folder
)
{

}



Node* Menu::root()
{
    return &_root;
}


}