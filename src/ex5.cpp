#include "Arduino.h"

#define LIGHT_PIN 33
#define BUTTON_PIN 25
#define YELLOW_LED_PIN 12

bool lastButtonState = LOW;

void setup(void)
{
    Serial.begin(115200);
    pinMode(LIGHT_PIN, INPUT);
    pinMode(BUTTON_PIN, INPUT);
    pinMode(YELLOW_LED_PIN, OUTPUT);
    digitalWrite(YELLOW_LED_PIN, LOW);
}

void loop(void)
{
    bool buttonState = digitalRead(BUTTON_PIN);

    if (buttonState == HIGH && lastButtonState == LOW) {
        int snapshot = analogRead(LIGHT_PIN);
        Serial.print("snapshot=");
        Serial.println(snapshot);

        digitalWrite(YELLOW_LED_PIN, HIGH);
        delay(100);
        digitalWrite(YELLOW_LED_PIN, LOW);
    }

    lastButtonState = buttonState;
    delay(10);
}