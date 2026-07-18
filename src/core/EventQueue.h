#ifndef EMBEDDED_UI_EVENT_QUEUE_H
#define EMBEDDED_UI_EVENT_QUEUE_H


#include <Arduino.h>

#include "Event.h"


namespace EmbeddedUI
{


/**
 * @brief Fila circular de eventos.
 */
class EventQueue
{

public:


    explicit EventQueue(
        uint8_t capacity = 16
    );



    ~EventQueue();



    /**
     * @brief Adiciona um evento ao final da fila.
     */
    bool push(
        const Event& event
    );



    /**
     * @brief Remove o primeiro evento da fila.
     */
    bool pop(
        Event& event
    );



    /**
     * @brief Informa se a fila está vazia.
     */
    bool empty() const;



    /**
     * @brief Informa se a fila está cheia.
     */
    bool full() const;



    /**
     * @brief Retorna a quantidade de eventos.
     */
    uint8_t count() const;



    /**
     * @brief Retorna a capacidade da fila.
     */
    uint8_t capacity() const;



    /**
     * @brief Remove todos os eventos da fila.
     */
    void clear();



private:


    EventQueue(
        const EventQueue&
    ) = delete;



    EventQueue& operator=(
        const EventQueue&
    ) = delete;



    Event* _events;


    uint8_t _capacity;


    uint8_t _head;


    uint8_t _tail;


    uint8_t _count;


};


}


#endif