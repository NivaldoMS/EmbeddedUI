#ifndef EMBEDDED_UI_INPUT_MANAGER_H
#define EMBEDDED_UI_INPUT_MANAGER_H


#include <Arduino.h>

#include "Encoder.h"
#include "../core/Event.h"
#include "../core/EventQueue.h"
#include "../input/InputEvent.h"


namespace EmbeddedUI
{


/**
 * @brief Camada de interpretação dos controles físicos.
 *
 * Converte eventos de hardware:
 *
 *   ROTATE_CW
 *   ROTATE_CCW
 *   BUTTON_DOWN
 *
 * em eventos da interface:
 *
 *   ENCODER_CW
 *   ENCODER_CCW
 *   BUTTON_ENTER
 *
 * Os eventos gerados são enviados para EventQueue.
 */
class UIInputManager
{

public:


    /**
     * @brief Cria o gerenciador de entrada.
     *
     * @param queue Fila de eventos da interface.
     */
    explicit UIInputManager(
        EventQueue& queue
    );



    /**
     * @brief Inicializa o gerenciador de entrada.
     */
    void begin(
        UIEncoder* encoder
    );



    /**
     * @brief Atualiza leitura dos dispositivos.
     *
     * Deve ser chamado no loop principal.
     */
    void update();



    /**
     * @brief Define evento gerado por pressão longa.
     *
     * Reservado para controle global:
     * abrir menu, sair, etc.
     */
    void setLongPressEvent(
        UIEventType event
    );



private:


    /**
     * @brief Encoder físico associado.
     */
    UIEncoder* encoder;



    /**
     * @brief Fila de eventos da interface.
     */
    EventQueue& eventQueue;



    /**
     * @brief Momento em que botão foi pressionado.
     */
    uint32_t pressStart;



    /**
     * @brief Estado do botão.
     */
    bool buttonPressed;



    /**
     * @brief Evento gerado por long press.
     */
    UIEventType longPressEvent;



    /**
     * @brief Tempo mínimo para considerar
     * pressão longa.
     */
    static constexpr uint16_t LONG_PRESS_TIME = 800;


};


}


#endif