#ifndef EMBEDDED_UI_VALUE_H
#define EMBEDDED_UI_VALUE_H


#include <Arduino.h>


namespace EmbeddedUI
{


/**
 * @brief Tipo de valor editável.
 */
enum class UIValueType : uint8_t
{
    NONE = 0,

    INTEGER,

    FLOAT,

    BOOLEAN,

    LIST
};



/**
 * @brief Classe base dos valores.
 */
class UIValue
{

public:


    UIValue(
        UIValueType type
    );


    virtual ~UIValue();



    /**
     * @brief Inicia edição.
     */
    virtual void beginEdit();


    /**
     * @brief Confirma alteração.
     */
    virtual void commit();


    /**
     * @brief Cancela alteração.
     */
    virtual void cancel();



    /**
     * @brief Incrementa valor.
     */
    virtual void increase();


    /**
     * @brief Decrementa valor.
     */
    virtual void decrease();



    /**
     * @brief Texto para exibição.
     *
     * Temporariamente retorna
     * uma string gerada pelo objeto.
     */
    virtual const char* text();



    UIValueType type() const;



protected:


    UIValueType valueType;


};





/**
 * @brief Valor inteiro.
 */
class UIIntValue : public UIValue
{

public:


    UIIntValue(
        int* value,
        int minimum,
        int maximum,
        int step = 1
    );


    void beginEdit() override;

    void commit() override;

    void cancel() override;


    void increase() override;

    void decrease() override;


    const char* text() override;



private:


    int* value;


    int backup;


    int minimum;


    int maximum;


    int step;


    char buffer[16];


};





/**
 * @brief Valor ponto flutuante.
 */
class UIFloatValue : public UIValue
{

public:


    UIFloatValue(
        float* value,
        float minimum,
        float maximum,
        float step
    );


    void beginEdit() override;

    void commit() override;

    void cancel() override;


    void increase() override;

    void decrease() override;


    const char* text() override;



private:


    float* value;


    float backup;


    float minimum;


    float maximum;


    float step;


    char buffer[20];

};





/**
 * @brief Valor booleano.
 */
class UIBoolValue : public UIValue
{

public:


    UIBoolValue(
        bool* value
    );


    void beginEdit() override;

    void commit() override;

    void cancel() override;


    void increase() override;

    void decrease() override;


    const char* text() override;



private:


    bool* value;


    bool backup;


};





/**
 * @brief Lista de opções.
 */
class UIListValue : public UIValue
{

public:


    UIListValue(
        uint8_t* value,
        const char* const* items,
        uint8_t count
    );


    void beginEdit() override;

    void commit() override;

    void cancel() override;


    void increase() override;

    void decrease() override;


    const char* text() override;



private:


    uint8_t* value;


    uint8_t backup;


    const char* const* items;


    uint8_t count;


};


}


#endif