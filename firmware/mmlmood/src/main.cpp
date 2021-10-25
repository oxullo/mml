#include <Arduino.h>

#include <Adafruit_DRV2605.h>

#define FASTLED_FORCE_SOFTWARE_PINS
#define FASTLED_INTERNAL
#include <FastLED.h>

#include "LIS2DTW12.h"

const uint8_t NUM_LEDS = 64;


CRGB leds[NUM_LEDS];
LIS2DTW12 accel;
Adafruit_DRV2605 haptics;


void matrix_test()
{
    static uint8_t lptr = 0;

    FastLED.clear();
    leds[lptr++] = CRGB::Red;
    FastLED.show();

    if (lptr == 64) {
        lptr = 0;
    }
}

void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(HAPTIC_EN_PIN, OUTPUT);
    digitalWrite(HAPTIC_EN_PIN, HIGH);

    FastLED.addLeds<WS2812B, MATRIX_PIN, GRB>(leds, NUM_LEDS);

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
    }

    EVERY_N_MILLISECONDS(16) {
        matrix_test();
    }

    EVERY_N_MILLISECONDS(500) {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }
}
