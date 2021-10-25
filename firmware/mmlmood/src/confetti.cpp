#include "confetti.h"
#include "matrix.h"

#define DEFAULT_PROBABILITY     30
#define FRAME_DELAY             33

Confetti::Confetti() :
    hue(0),
    probability(DEFAULT_PROBABILITY)
{
    frame_delay = FRAME_DELAY;
}

// adapted from https://github.com/FastLED/FastLED/blob/master/examples/DemoReel100/DemoReel100.ino
void Confetti::render()
{
    EVERY_N_MILLIS(500) {
        ++hue;
    }
    // random colored speckles that blink in and fade smoothly
    fadeToBlackBy(leds, NUM_LEDS, 10);

    if (random8(100) < probability) {
        int pos = random16(NUM_LEDS);
        leds[pos] += CHSV(hue + random8(64), 200, 255);
    }

    FastLED.show();
}


Confetti confetti;
