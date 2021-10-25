#include "matrix.h"
#include "swirl.h"

#define BORDER          1
#define FRAME_DELAY     33


Swirl::Swirl()
{
    frame_delay = FRAME_DELAY;
}

// Taken from https://gist.github.com/kriegsman/5adca44e14ad025e6d3b
void Swirl::render()
{
    // Apply some blurring to whatever's already on the matrix
    // Note that we never actually clear the matrix, we just constantly
    // blur it repeatedly.  Since the blurring is 'lossy', there's
    // an automatic trend toward black -- by design.
    uint8_t blurAmount = beatsin8(2,10,255);
    blur2d(leds, MATRIX_WIDTH, MATRIX_HEIGHT, blurAmount);

    // Use two out-of-sync sine waves
    uint8_t  i = beatsin8( 27, BORDER, MATRIX_HEIGHT-BORDER);
    uint8_t  j = beatsin8( 41, BORDER, MATRIX_WIDTH-BORDER);
    // Also calculate some reflections
    uint8_t ni = (MATRIX_WIDTH-1)-i;
    uint8_t nj = (MATRIX_WIDTH-1)-j;

    // The color of each point shifts over time, each at a different speed.
    uint16_t ms = millis();
    leds[XY( i, j)] += CHSV( ms / 11, 200, 255);
    leds[XY( j, i)] += CHSV( ms / 13, 200, 255);
    leds[XY(ni,nj)] += CHSV( ms / 17, 200, 255);
    leds[XY(nj,ni)] += CHSV( ms / 29, 200, 255);
    leds[XY( i,nj)] += CHSV( ms / 37, 200, 255);
    leds[XY(ni, j)] += CHSV( ms / 41, 200, 255);

    FastLED.show();
}

Swirl swirl;
