#ifndef EMBEDDED_UI_FONT_H
#define EMBEDDED_UI_FONT_H


#include <Arduino.h>


namespace EmbeddedUI
{


struct Glyph
{

    const uint8_t* bitmap;


    uint8_t width;


    uint8_t height;


};



/**
 * @brief Descritor abstrato de fonte.
 *
 * O ponteiro data contém a representação
 * nativa esperada pelo driver de display.
 *
 * Para U8g2, data deve apontar para uma fonte
 * no formato u8g2_font_t.
 */
class Font
{

public:


    Font(
        const uint8_t* data = nullptr,
        uint8_t width = 0,
        uint8_t height = 0
    );



    /**
     * @brief Retorna os dados nativos da fonte.
     */
    const uint8_t* data() const;



    /**
     * @brief Retorna a largura média declarada.
     */
    uint8_t width() const;



    /**
     * @brief Retorna a altura declarada.
     */
    uint8_t height() const;



    /**
     * @brief Retorna um descritor de glifo.
     *
     * A busca individual depende do formato
     * específico da fonte.
     */
    Glyph glyph(
        char character
    ) const;



    /**
     * @brief Informa se existe uma fonte associada.
     */
    bool valid() const;



private:


    const uint8_t* _data;


    uint8_t _width;


    uint8_t _height;


};


}


#endif