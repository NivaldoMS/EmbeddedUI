#ifndef EMBEDDED_UI_INPUT_MANAGER_H
#define EMBEDDED_UI_INPUT_MANAGER_H


#include <Arduino.h>

#include "Encoder.h"
#include "Event.h"
#include "InputEvent.h"


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
 */
class UIInputManager
{

public:


    UIInputManager();



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
     * @brief Verifica se existe evento disponível.
     */
    bool available();



    /**
     * @brief Obtém evento pendente.
     */
    UIEvent read();



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
     * @brief Último evento convertido.
     */
    UIEvent pending;



    /**
     * @brief Indica evento aguardando leitura.
     */
    bool hasEvent;



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