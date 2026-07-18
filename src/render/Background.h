#ifndef EMBEDDED_UI_BACKGROUND_H
#define EMBEDDED_UI_BACKGROUND_H


#include "Bitmap.h"


namespace EmbeddedUI
{


class UIDisplayDriver;


/**
 * @brief Gerenciador do plano de fundo.
 */
class UIBackground
{

public:


    UIBackground();



    /**
     * @brief Define bitmap de fundo.
     */
    void setBitmap(
        const UIBitmap* bitmap
    );



    /**
     * @brief Remove fundo.
     */
    void clear();



    /**
     * @brief Desenha fundo.
     */
    void draw(
        UIDisplayDriver* display
    );



private:


    const UIBitmap* bitmap;


};



}


#endif