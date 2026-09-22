#include "Arduino.h"

#define LIGHT_PIN 33

unsigned long lastRead = 0;
const unsigned long INTERVAL = 500;

void setup(void)
{
    Serial.begin(115200);
    pinMode(LIGHT_PIN, INPUT);
}

void loop(void)
{
    unsigned long now = millis();
    if (now - lastRead >= INTERVAL) {
        lastRead = now;
        int raw = analogRead(LIGHT_PIN);
        Serial.print("raw=");
        Serial.println(raw);
    }
}