#ifndef EMBEDDED_UI_ENCODER_H
#define EMBEDDED_UI_ENCODER_H


#include <Arduino.h>

#include "InputEvent.h"


namespace EmbeddedUI
{


/**
 * @brief Encoder rotativo com botão.
 *
 * Produz apenas InputEvent.
 */
class Encoder
{

public:


    Encoder(
        uint8_t pinA,
        uint8_t pinB,
        uint8_t buttonPin
    );



    /**
     * @brief Inicializa os pinos e estados.
     */
    void begin();



    /**
     * @brief Atualiza a leitura do encoder.
     */
    void update();



    /**
     * @brief Informa se existe InputEvent pendente.
     */
    bool available() const;



    /**
     * @brief Retorna o próximo InputEvent.
     */
    InputEvent read();



private:


    /**
     * @brief Adiciona um evento à fila interna.
     */
    bool enqueue(
        const InputEvent& event
    );



    /**
     * @brief Atualiza a rotação.
     */
    void updateRotation();



    /**
     * @brief Atualiza o botão.
     */
    void updateButton();



    uint8_t _pinA;


    uint8_t _pinB;


    uint8_t _buttonPin;



    uint8_t _lastA;


    uint8_t _buttonState;


    uint8_t _lastButtonReading;



    uint32_t _lastDebounceTime;



    static constexpr uint16_t DEBOUNCE_TIME =
        40;



    static constexpr uint8_t EVENT_CAPACITY =
        8;



    InputEvent _events[EVENT_CAPACITY];


    uint8_t _head;


    uint8_t _tail;


    uint8_t _count;


};


}


#endif