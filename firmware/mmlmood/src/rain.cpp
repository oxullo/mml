#include <stdint.h>
#include <string.h>

#include "matrix.h"
#include "rain.h"



Drop::Drop() :
        alive(false),
        x(0),
        y(0),
        friction(0)
{
}

bool Drop::is_alive()
{
    return alive;
}

void Drop::reset()
{
    alive = false;
}

void Drop::start()
{
    x = random8(MATRIX_WIDTH);
    y = 0;
    friction = 1 - random8(9) / 10.0;
    alive = true;
}

void Drop::step()
{
    // TODO: add imu readout accessor
//    x += imu.a.x / 2 * friction;
//    y += imu.a.y / 2 * friction;
    x += 1;
    y += 1;

    if (x < 0) {
        x = 0;
    }

    if (x > MATRIX_WIDTH - 1) {
        x = MATRIX_WIDTH - 1;
    }

    if (y > MATRIX_HEIGHT - 1) {
        alive = false;
    }
}

uint8_t Drop::get_x()
{
    return (uint8_t)x;
}

uint8_t Drop::get_y()
{
    return (uint8_t)y;
}


Rain::Rain()
{

}

void Rain::reset()
{
    for (uint8_t i = 0 ; i < MAX_DROPS ; ++i) {
        drops[i].reset();
    }
}

void Rain::render()
{
    fadeToBlackBy(leds, NUM_LEDS, 40);

    for (uint8_t i = 0 ; i < MAX_DROPS ; ++i) {
        if (drops[i].is_alive()) {
            leds[XY(drops[i].get_x(), drops[i].get_y())] = CRGB::Blue;
            drops[i].step();
        }
    }

    if (random8(100) > 90) {
        for (uint8_t i = 0 ; i < MAX_DROPS ; ++i) {
            if (!drops[i].is_alive()) {
                drops[i].start();
                break;
            }
        }
    }

    FastLED.show();
}

Rain rain;
