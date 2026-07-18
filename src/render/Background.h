#ifndef EMBEDDED_UI_BACKGROUND_H
#define EMBEDDED_UI_BACKGROUND_H


#include "Bitmap.h"


namespace EmbeddedUI
{


class DisplayDriver;


/**
 * @brief Gerencia o bitmap de fundo.
 *
 * Não assume propriedade sobre o Bitmap.
 */
class Background
{

public:


    Background();



    /**
     * @brief Define o bitmap de fundo.
     */
    void setBitmap(
        const Bitmap* bitmap
    );



    /**
     * @brief Remove o bitmap associado.
     */
    void clear();



    /**
     * @brief Retorna o bitmap associado.
     */
    const Bitmap* bitmap() const;



    /**
     * @brief Desenha o bitmap associado.
     */
    void draw(
        DisplayDriver& display
    ) const;



private:


    const Bitmap* _bitmap;


};


}


#endif