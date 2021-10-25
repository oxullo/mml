#include <Arduino.h>

#include <Adafruit_DRV2605.h>

#include "imu.h"
#include "matrix.h"
#include "animator.h"

#include "rain.h"
#include "confetti.h"
#include "noise.h"
#include "swirl.h"


const uint16_t TILT_THRESHOLD_MIN = 2000;
const uint16_t TILT_THRESHOLD_MAX = 7500;

CRGB leds[NUM_LEDS];

IMU imu;
Adafruit_DRV2605 haptics;
Animator* animators_map[IMU::MAX_ORIENTATIONS];


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

    imu.begin(TILT_THRESHOLD_MIN, TILT_THRESHOLD_MAX);
    haptics.begin();
    haptics.selectLibrary(1);
    haptics.setMode(DRV2605_MODE_INTTRIG);
    haptics.setWaveform(0, 1);
    haptics.setWaveform(1, 0);

    animators_map[IMU::ORIENTATION_VERTICAL_NORMAL] = &rain;
    animators_map[IMU::ORIENTATION_VERTICAL_90CW] = &confetti;
    animators_map[IMU::ORIENTATION_VERTICAL_90CCW] = &noise;
    animators_map[IMU::ORIENTATION_VERTICAL_180] = &swirl;
//    animators_map[IMU::ORIENTATION_HORIZONTAL_TOP] = &ballgame;
//    animators_map[IMU::ORIENTATION_HORIZONTAL_BOTTOM] = &flashlight;
    animators_map[IMU::ORIENTATION_HORIZONTAL_TOP] = NULL;
    animators_map[IMU::ORIENTATION_HORIZONTAL_BOTTOM] = NULL;
    animators_map[IMU::ORIENTATION_UNKNOWN] = NULL;


    tester();
}

void loop()
{
    static uint32_t ts_lastframe = 0;

    IMU::Orientation new_orientation = imu.update();

    if (new_orientation != IMU::ORIENTATION_UNKNOWN) {
        if (animators_map[new_orientation]) {
            animators_map[new_orientation]->reset();
        }
    }

    Animator *current_animator = animators_map[imu.get_orientation()];

    if (current_animator && millis() - ts_lastframe > current_animator->frame_delay) {
        ts_lastframe = millis();
        current_animator->render();
    }

    EVERY_N_MILLISECONDS(500) {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }
}
