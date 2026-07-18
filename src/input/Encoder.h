#ifndef EMBEDDED_UI_ENCODER_H
#define EMBEDDED_UI_ENCODER_H


#include <Arduino.h>

#include "InputEvent.h"


namespace EmbeddedUI
{


/**
 * @brief Encoder rotativo com botão.
 *
 * Gera eventos para a interface.
 */
class UIEncoder
{

public:


    UIEncoder(
        uint8_t pinA,
        uint8_t pinB,
        uint8_t buttonPin
    );



    /**
     * @brief Inicializa pinos.
     */
    void begin();



    /**
     * @brief Atualiza leitura do encoder.
     *
     * Deve ser chamado no loop().
     */
    void update();



    /**
     * @brief Verifica se existe evento pendente.
     */
    bool available();



    /**
     * @brief Obtém próximo evento.
     */
    UIEvent read();



private:


    uint8_t pinA;

    uint8_t pinB;

    uint8_t buttonPin;



    uint8_t lastA;

    uint8_t lastButton;



    UIInputEvent pendingEvent;



    bool eventAvailable;



    uint32_t lastButtonTime;



    static constexpr uint16_t DEBOUNCE_TIME = 40;



    void updateRotation();

    void updateButton();


};


}


#endif