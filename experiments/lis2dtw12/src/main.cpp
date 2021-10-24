#include <Arduino.h>
#include <Wire.h>

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
    SerialUSB.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);

    accel.begin();
}

void loop()
{
    if (accel.is_data_ready()) {
        accel.read();

        SerialUSB.print(accel.mg().x);
        SerialUSB.print(" ");
        SerialUSB.print(accel.mg().y);
        SerialUSB.print(" ");
        SerialUSB.println(accel.mg().z);
    }
    blink();
}
