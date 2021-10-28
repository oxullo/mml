/*
 * heart.cpp
 *
 *  Created on: Oct 28, 2021
 *      Author: xi
 */


#include <stdint.h>
#include <avr/pgmspace.h>

#include "matrix.h"


namespace {
const uint8_t HEARTH_COLS = 16;

const uint8_t heart[HEARTH_COLS] PROGMEM = {0, 0, 0, 0, 0, 0, 0, 0x1e, 0x3f, 0x7f, 0xfe, 0xfe, 0x7f, 0x3f, 0x1e};
}

void play_heart()
{
    for (uint16_t pos = 0 ; pos < HEARTH_COLS - 8 ; ++pos) {
        FastLED.clear();

        for (uint8_t x=0 ; x < MATRIX_WIDTH ; ++x) {
            uint8_t column = pgm_read_byte(&(heart[x+pos]));

            for (uint8_t y=0 ; y < MATRIX_HEIGHT ; ++y) {
                if (column & (1 << y)) {
                    leds[XY(x, y)] = CRGB(190, 0, 0);
                }
            }
        }

        FastLED.show();
        delay(66);
    }
    delay(1000);
}
