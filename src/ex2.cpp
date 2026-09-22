#include "Arduino.h"

#define GREEN_LED_PIN 27
#define BUTTON_PIN 25

bool greenState = false;
bool lastButtonState = LOW;

void setup(void)
{
    Serial.begin(115200);
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT); // подтяжка к GND уже есть в схеме (резистор r5)
    digitalWrite(GREEN_LED_PIN, LOW);
}

void loop(void)
{
    bool buttonState = digitalRead(BUTTON_PIN);

    if (buttonState == HIGH && lastButtonState == LOW) {
        greenState = !greenState;
        digitalWrite(GREEN_LED_PIN, greenState ? HIGH : LOW);
        Serial.println(greenState ? "GREEN=1" : "GREEN=0");
        delay(50); // защита от дребезга контактов
    }

    lastButtonState = buttonState;
}