#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>

const uint8_t MATRIX_WIDTH = 8;
const uint8_t MATRIX_HEIGHT = 8;
#define MAX_DIMENSION ((MATRIX_WIDTH > MATRIX_HEIGHT) ? MATRIX_WIDTH : MATRIX_HEIGHT)
#define NUM_LEDS (MATRIX_WIDTH * MATRIX_HEIGHT)

inline uint16_t XY(uint8_t x, uint8_t y)
{
    uint16_t xc = min(max(x, 0), MATRIX_WIDTH - 1);
    uint16_t yc = min(max(y, 0), MATRIX_HEIGHT - 1);

    return (yc * MATRIX_WIDTH) + xc;
}

#endif
