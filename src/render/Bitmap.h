#ifndef EMBEDDED_UI_BITMAP_H
#define EMBEDDED_UI_BITMAP_H


#include <Arduino.h>


namespace EmbeddedUI
{


/**
 * @brief Bitmap armazenado em memória de programa.
 */
struct UIBitmap
{

    const uint8_t* data;

    uint16_t width;

    uint16_t height;


};



}


#endif