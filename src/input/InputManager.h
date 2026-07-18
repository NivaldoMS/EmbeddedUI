#ifndef EMBEDDED_UI_INPUT_MANAGER_H
#define EMBEDDED_UI_INPUT_MANAGER_H


#include <Arduino.h>

#include "Encoder.h"
#include "InputEvent.h"

#include "../core/Event.h"
#include "../core/EventQueue.h"


namespace EmbeddedUI
{


/**
 * @brief Interpreta eventos produzidos pelos
 * dispositivos físicos.
 *
 * Converte InputEvent em Event.
 */
class InputManager
{

public:


    /**
     * @brief Cria o gerenciador de entrada.
     *
     * @param capacity Capacidade da fila interna.
     */
    explicit InputManager(
        uint8_t capacity = 16
    );



    /**
     * @brief Associa um encoder ao gerenciador.
     *
     * O InputManager não é proprietário
     * do encoder.
     */
    void attach(
        Encoder& encoder
    );



    /**
     * @brief Remove o encoder associado.
     */
    void detach();



    /**
     * @brief Inicializa os dispositivos associados.
     */
    void begin();



    /**
     * @brief Atualiza a leitura e interpretação
     * dos dispositivos.
     */
    void update();



    /**
     * @brief Informa se existe evento pendente.
     */
    bool available() const;



    /**
     * @brief Retorna o próximo evento pendente.
     *
     * Retorna EventType::NONE quando a fila
     * estiver vazia.
     */
    Event read();



    /**
     * @brief Define o evento produzido por
     * uma pressão longa.
     */
    void setLongPressEvent(
        EventType event
    );



private:


    void processInputEvent(
        const InputEvent& event
    );



    Encoder* _encoder;


    EventQueue _events;


    uint32_t _pressStart;


    bool _buttonPressed;


    bool _longPressTriggered;


    EventType _longPressEvent;



    static constexpr uint16_t LONG_PRESS_TIME =
        800;


};


}


#endif