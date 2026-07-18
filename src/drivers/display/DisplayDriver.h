#ifndef EMBEDDED_UI_DISPLAY_DRIVER_H
#define EMBEDDED_UI_DISPLAY_DRIVER_H


#include <Arduino.h>

#include "../../render/Bitmap.h"


namespace EmbeddedUI
{


class Font;


/**
 * @brief Interface abstrata para drivers de display.
 */
class DisplayDriver
{

public:


    virtual ~DisplayDriver()
    {

    }



    /**
     * @brief Inicializa o display.
     */
    virtual void begin() = 0;



    /**
     * @brief Limpa o buffer de desenho.
     */
    virtual void clear() = 0;



    /**
     * @brief Envia o buffer ao display físico.
     */
    virtual void refresh() = 0;



    /**
     * @brief Define a fonte usada pelo driver.
     */
    virtual void setFont(
        const Font& font
    ) = 0;



    /**
     * @brief Define a cor ou modo de desenho.
     *
     * A interpretação do valor depende
     * da implementação do driver.
     */
    virtual void setDrawColor(
        uint16_t color
    ) = 0;



    /**
     * @brief Desenha texto.
     */
    virtual void drawText(
        int16_t x,
        int16_t y,
        const char* text
    ) = 0;



    /**
     * @brief Desenha o contorno de um retângulo.
     */
    virtual void drawRect(
        int16_t x,
        int16_t y,
        int16_t width,
        int16_t height
    ) = 0;



    /**
     * @brief Desenha um retângulo preenchido.
     */
    virtual void fillRect(
        int16_t x,
        int16_t y,
        int16_t width,
        int16_t height
    ) = 0;



    /**
     * @brief Desenha um bitmap.
     */
    virtual void drawBitmap(
        int16_t x,
        int16_t y,
        const Bitmap& bitmap
    ) = 0;



    /**
     * @brief Retorna a largura do display.
     */
    virtual uint16_t width() const = 0;



    /**
     * @brief Retorna a altura do display.
     */
    virtual uint16_t height() const = 0;


};


}


#endif