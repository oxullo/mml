#include <Arduino.h>

#include <Adafruit_DRV2605.h>

#define FASTLED_FORCE_SOFTWARE_PINS
#define FASTLED_INTERNAL
#include <FastLED.h>

#include "imu.h"
#include "matrix.h"


CRGB leds[NUM_LEDS];

IMU imu;
Adafruit_DRV2605 haptics;


void tester()
{
    for (uint8_t i=0 ; i < MATRIX_WIDTH ; ++i) {
        leds[XY(i, i)] = CRGB::Red;
        FastLED.show();
        delay(100);
    }

    for (uint8_t i=0 ; i < MATRIX_WIDTH ; ++i) {
        leds[XY(MATRIX_WIDTH - i - 1, i)] = CRGB::Green;
        FastLED.show();
        delay(100);
    }
    delay(1000);

    FastLED.clear();
    FastLED.show();
}


void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(HAPTIC_EN_PIN, OUTPUT);
    digitalWrite(HAPTIC_EN_PIN, HIGH);

    FastLED.addLeds<WS2812B, MATRIX_PIN, GRB>(leds, NUM_LEDS);

    imu.begin();
    haptics.begin();
    haptics.selectLibrary(1);
    haptics.setMode(DRV2605_MODE_INTTRIG);
    haptics.setWaveform(0, 1);
    haptics.setWaveform(1, 0);

    tester();
}

void loop()
{
    imu.update();

    EVERY_N_MILLISECONDS(500) {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }
}
