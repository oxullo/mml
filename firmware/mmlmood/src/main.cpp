#include <Arduino.h>
#include <heart.h>

#include "imu.h"
#include "haptics.h"
#include "matrix.h"
#include "animator.h"

#include "rain.h"
#include "confetti.h"
#include "noise.h"
#include "swirl.h"
#include "ballgame.h"
#include "flashlight.h"
#include "heart.h"


const float TILT_THRESHOLD_MIN = 0.4;
const float TILT_THRESHOLD_MAX = 0.7;

CRGB leds[NUM_LEDS];

Animator* animators_map[IMU::MAX_ORIENTATIONS];


void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);

    FastLED.addLeds<WS2812B, MATRIX_PIN, GRB>(leds, NUM_LEDS);

    haptics.begin();

    imu.begin(TILT_THRESHOLD_MIN, TILT_THRESHOLD_MAX);

    animators_map[IMU::ORIENTATION_VERTICAL_NORMAL] = &rain;
    animators_map[IMU::ORIENTATION_VERTICAL_90CW] = &confetti;
    animators_map[IMU::ORIENTATION_VERTICAL_90CCW] = &noise;
    animators_map[IMU::ORIENTATION_VERTICAL_180] = &swirl;
    animators_map[IMU::ORIENTATION_HORIZONTAL_TOP] = &ballgame;
    animators_map[IMU::ORIENTATION_HORIZONTAL_BOTTOM] = &flashlight;
    animators_map[IMU::ORIENTATION_UNKNOWN] = NULL;


    play_heart();
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
