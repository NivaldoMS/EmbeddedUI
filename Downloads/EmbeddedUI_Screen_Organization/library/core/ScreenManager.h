#ifndef EMBEDDED_UI_SCREEN_MANAGER_H
#define EMBEDDED_UI_SCREEN_MANAGER_H


#include "Screen.h"


namespace EmbeddedUI
{


class DisplayDriver;


/**
 * @brief Gerencia a tela atualmente ativa.
 *
 * O ScreenManager não é proprietário das telas.
 */
class ScreenManager
{

public:


    ScreenManager();


    void begin();


    void show(
        Screen& screen
    );


    void clear();


    Screen* current() const;


    void update();


    Result handleEvent(
        const Event& event
    );


    void render(
        DisplayDriver& display
    );


private:


    Screen* _current;

};


}


#endif
