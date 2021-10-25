#include <stdint.h>

#include "matrix.h"
#include "noise.h"

#define DEFAULT_SPEED       5
#define DEFAULT_SCALE       100

Noise::Noise() :
    speed(DEFAULT_SPEED),
    scale(DEFAULT_SCALE)
{
    reset();
}

void Noise::reset()
{
    x = random16();
    y = random16();
    z = random16();
}

// adapted from https://github.com/FastLED/FastLED/blob/master/examples/Noise/Noise.ino
void Noise::render()
{
    for (int i = 0; i < MAX_DIMENSION; i++) {
        int ioffset = scale * i;

        for (int j = 0; j < MAX_DIMENSION; j++) {
            int joffset = scale * j;
            noisemap[i][j] = inoise8(x + ioffset, y + joffset, z);
        }
    }
    z += speed;

    for(int i = 0; i < MATRIX_WIDTH; i++) {
        for(int j = 0; j < MATRIX_HEIGHT; j++) {
            // We use the value at the (i,j) coordinate in the noise
            // array for our brightness, and the flipped value from (j,i)
            // for our pixel's hue.
            leds[XY(i, j)] = CHSV(noisemap[j][i], 255, noisemap[i][j]);
        }
    }

    FastLED.show();
}

Noise noise;
