#ifndef EMBEDDED_UI_DISPLAY_DRIVER_H
#define EMBEDDED_UI_DISPLAY_DRIVER_H


#include <Arduino.h>

#include "../../render/Bitmap.h"

namespace EmbeddedUI
{


/**
 * @brief Interface abstrata para drivers de display.
 */
class UIDisplayDriver
{

public:


    virtual ~UIDisplayDriver()
    {
    }



    /**
     * @brief Inicializa o display.
     */
    virtual void begin() = 0;



    /**
     * @brief Limpa a tela.
     */
    virtual void clear() = 0;



    /**
     * @brief Atualiza o display físico.
     */
    virtual void refresh() = 0;



    /**
     * @brief Desenha texto.
     */
    virtual void drawText(
        int16_t x,
        int16_t y,
        const char* text
    ) = 0;



    /**
     * @brief Desenha retângulo.
     */
    virtual void drawRect(
        int16_t x,
        int16_t y,
        int16_t width,
        int16_t height
    ) = 0;



    /**
     * @brief Preenche retângulo.
     */
    virtual void fillRect(
        int16_t x,
        int16_t y,
        int16_t width,
        int16_t height
    ) = 0;



    /**
     * @brief Largura do display.
     */
    virtual uint16_t width() const = 0;



    /**
     * @brief Altura do display.
     */
    virtual uint16_t height() const = 0;

    virtual void drawBitmap(
        int16_t x,
        int16_t y,
        const UIBitmap& bitmap
    )
    {
    }

};


}


#endif