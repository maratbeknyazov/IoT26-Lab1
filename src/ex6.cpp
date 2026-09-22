#include "Arduino.h"

#define BLUE_LED_PIN 14

void setup(void)
{
    Serial.begin(115200);
    pinMode(BLUE_LED_PIN, OUTPUT);
    digitalWrite(BLUE_LED_PIN, LOW);
}

void loop(void)
{
    if (Serial.available() > 0) {
        char c = Serial.read();

        if (c == 'B') {
            digitalWrite(BLUE_LED_PIN, HIGH);
            Serial.println("BLUE=1");
        } else if (c == 'b') {
            digitalWrite(BLUE_LED_PIN, LOW);
            Serial.println("BLUE=0");
        }
    }
}