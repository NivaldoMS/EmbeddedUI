#ifndef MENU_APPLICATION_H
#define MENU_APPLICATION_H


#include <EmbeddedUI.h>


using namespace EmbeddedUI;


/**
 * @brief Aplicação de demonstração do sistema de menu.
 *
 * Mantém os nós em armazenamento estático e utiliza
 * Builder para configurar e montar a árvore.
 */
class MenuApplication
{

public:


    explicit MenuApplication(
        DisplayDriver& display
    );



    /**
     * @brief Inicializa a aplicação.
     */
    void begin(
        InputDevice& inputDevice
    );



    /**
     * @brief Atualiza entrada, telas e renderização.
     */
    void update();



    /**
     * @brief Retorna o menu da aplicação.
     */
    Menu& menu();


    const Menu& menu() const;



    /**
     * @brief Retorna o nó atualmente selecionado.
     */
    Node* selectedNode();



    /**
     * @brief Retorna o nó atualmente em edição.
     *
     * Retorna nullptr quando nenhum ValueNode estiver
     * sendo editado.
     */
    Node* editingNode();



    /**
     * @brief Retorna o nó cuja ação está sendo executada.
     */
    Node* executingNode();



    /**
     * @brief Define o nó cuja ação está em execução.
     */
    void startExecuting(
        Node* node
    );



    /**
     * @brief Finaliza a execução da ação atual.
     */
    void stopExecuting();



private:


    /**
     * @brief Configura a aparência da interface.
     */
    void configureTheme();



    /**
     * @brief Configura os nós e monta a árvore do menu.
     *
     * A legenda, o tipo, a faixa, o passo e o valor inicial
     * dos ValueNode são definidos pelo Builder.
     */
    void buildMenu();



    DisplayDriver& _display;


    InputManager _input;


    Theme _theme;


    Font _font;


    Renderer _renderer;


    Engine _engine;



    Menu _menu;


    MenuScreen _menuScreen;



    /*
     * --------------------------------------------------------
     * Menu Audio
     * --------------------------------------------------------
     */

    Node _audioFolder;


    ValueNode _volumeValue;

    ValueNode _balValue;

    ValueNode _bassValue;

    ValueNode _midValue;

    ValueNode _trebleValue;

    ValueNode _enabledValue;

    ListNode _freqValue;



    /*
     * --------------------------------------------------------
     * Menu Display
     * --------------------------------------------------------
     */

    Node _displayFolder;


    ValueNode _brightnessValue;

    ValueNode _contrastValue;



    /*
     * --------------------------------------------------------
     * Menu System
     * --------------------------------------------------------
     */

    Node _systemFolder;


    Node _informationAction;

    Node _resetAction;



    /**
     * Deve ser declarado depois de _menu, pois recebe
     * uma referência para ele no construtor.
     */
    Builder _builder;



    /**
     * Nó de ação atualmente em execução.
     *
     * O ponteiro não possui propriedade sobre o nó.
     */
    Node* _executingNode;


};


#endif