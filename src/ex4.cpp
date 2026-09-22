#include "Arduino.h"

#define LIGHT_PIN 33
#define BLUE_LED_PIN 14
#define GREEN_LED_PIN 27
#define YELLOW_LED_PIN 12
#define RED_LED_PIN 26

unsigned long lastRead = 0;
const unsigned long INTERVAL = 500;

void setup(void)
{
    Serial.begin(115200);
    pinMode(LIGHT_PIN, INPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(YELLOW_LED_PIN, OUTPUT);
    pinMode(RED_LED_PIN, OUTPUT);
}

void loop(void)
{
    unsigned long now = millis();
    if (now - lastRead >= INTERVAL) {
        lastRead = now;
        int raw = analogRead(LIGHT_PIN);

        digitalWrite(BLUE_LED_PIN, LOW);
        digitalWrite(GREEN_LED_PIN, LOW);
        digitalWrite(YELLOW_LED_PIN, LOW);
        digitalWrite(RED_LED_PIN, LOW);

        const char* band;
        if (raw <= 1023) {
            digitalWrite(BLUE_LED_PIN, HIGH);
            band = "BLUE";
        } else if (raw <= 2047) {
            digitalWrite(GREEN_LED_PIN, HIGH);
            band = "GREEN";
        } else if (raw <= 3071) {
            digitalWrite(YELLOW_LED_PIN, HIGH);
            band = "YELLOW";
        } else {
            digitalWrite(RED_LED_PIN, HIGH);
            band = "RED";
        }

        Serial.print("band=");
        Serial.println(band);
    }
}