#include <Arduino.h>

#include <Adafruit_DRV2605.h>

#include "LIS2DTW12.h"

LIS2DTW12 accel;
Adafruit_DRV2605 haptics;


void blink()
{
    static uint32_t ts_lastblink = 0;

    if (millis() - ts_lastblink > 200) {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        ts_lastblink = millis();
        haptics.go();
    }
}

void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(HAPTIC_EN_PIN, OUTPUT);

    digitalWrite(HAPTIC_EN_PIN, HIGH);

    accel.begin();
    haptics.begin();
    haptics.selectLibrary(1);
    haptics.setMode(DRV2605_MODE_INTTRIG);
    haptics.setWaveform(0, 1);
    haptics.setWaveform(1, 0);
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
