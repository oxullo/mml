#include "matrix.h"
#include "imu.h"
#include "haptics.h"

#include "ballgame.h"

#define FRAME_DELAY         5


Ballgame::Ballgame() :
        vx(0),
        vy(0),
        ballx(3),
        bally(3)
{
    frame_delay = FRAME_DELAY;
}

void Ballgame::reset()
{
    ballx = 3;
    bally = 3;
}

void Ballgame::render()
{
    int8_t bmx = (int8_t)ballx, bmy = (int8_t)bally;

    vx *= 0.99;
    vy *= 0.99;

    if ((bmx < MATRIX_WIDTH - 1 && imu.norm().x > 0) || (bmx > 0 && imu.norm().x < 0)) {
        vx += imu.norm().x * 0.01;
    }

    if ((bmy < MATRIX_HEIGHT - 1 && imu.norm().y > 0) || (bmy > 0 && imu.norm().y < 0)) {
        vy += imu.norm().y * 0.01;
    }

    ballx = ballx + vx;
    bally = bally + vy;
    bmx = (int8_t)ballx;
    bmy = (int8_t)bally;

    if (bmx > MATRIX_WIDTH - 1 || bmx < 0) {
        haptics.trigger(1);
        vx = -vx * 0.8;

        if (bmx > MATRIX_WIDTH - 1) {
            ballx = MATRIX_WIDTH - 1;
        } else {
            ballx = 0;
        }
    }

    if (bmy > MATRIX_HEIGHT - 1 || bmy < 0) {
        haptics.trigger(1);
        vy = -vy * 0.8;

        if (bmy > MATRIX_HEIGHT - 1) {
            bally = MATRIX_HEIGHT - 1;
        } else {
            bally = 0;
        }
    }

    bmx = (int8_t)ballx;
    bmy = (int8_t)bally;

    fadeToBlackBy(leds, NUM_LEDS, 20);
    leds[XY(bmx, bmy)] = CRGB::White;

    FastLED.show();
}

Ballgame ballgame;
