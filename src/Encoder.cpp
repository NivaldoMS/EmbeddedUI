#include "Encoder.h"


namespace EmbeddedUI
{


UIEncoder::UIEncoder(
    uint8_t pinA,
    uint8_t pinB,
    uint8_t buttonPin
)
:
pinA(pinA),
pinB(pinB),
buttonPin(buttonPin),
lastA(HIGH),
lastButton(HIGH),
pendingEvent(),
eventAvailable(false),
lastButtonTime(0)
{

}



void UIEncoder::begin()
{

    pinMode(
        pinA,
        INPUT_PULLUP
    );


    pinMode(
        pinB,
        INPUT_PULLUP
    );


    pinMode(
        buttonPin,
        INPUT_PULLUP
    );


    lastA = digitalRead(pinA);

    lastButton = digitalRead(buttonPin);

}



void UIEncoder::update()
{

    updateRotation();

    updateButton();

}



void UIEncoder::updateRotation()
{

    uint8_t currentA = digitalRead(pinA);


    if(currentA != lastA)
    {

        if(digitalRead(pinB) != currentA)
        {
            pendingEvent =
                UIEvent(
                    UIEventType::ENCODER_CW,
                    millis()
                );
        }
        else
        {
            pendingEvent =
                UIEvent(
                    UIEventType::ENCODER_CCW,
                    millis()
                );
        }


        eventAvailable = true;
    }


    lastA = currentA;

}



void UIEncoder::updateButton()
{

    uint8_t currentButton =
        digitalRead(buttonPin);



    if(currentButton != lastButton)
    {

        uint32_t now = millis();



        if(
            now - lastButtonTime
            > DEBOUNCE_TIME
        )
        {

            if(currentButton == LOW)
            {

                pendingEvent =
                    UIEvent(
                        UIEventType::BUTTON_ENTER,
                        now
                    );


                eventAvailable = true;

            }


            lastButtonTime = now;

        }

    }


    lastButton = currentButton;

}



bool UIEncoder::available()
{
    return eventAvailable;
}



UIEvent UIEncoder::read()
{

    eventAvailable = false;


    return pendingEvent;

}


}