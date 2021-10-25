#include <Arduino.h>

#include "LIS2DTW12.h"

LIS2DTW12 accel;


void blink()
{
    static uint32_t ts_lastblink = 0;

    if (millis() - ts_lastblink > 200) {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        ts_lastblink = millis();
    }
}

void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    accel.begin();
}

void loop()
{
    if (accel.is_data_ready()) {
        accel.read();

        Serial.print(accel.mg().x);
        Serial.print(" ");
        Serial.print(accel.mg().y);
        Serial.print(" ");
        Serial.println(accel.mg().z);

        blink();
    }
}
