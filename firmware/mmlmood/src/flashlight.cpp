#include "matrix.h"
#include "flashlight.h"

#define FRAME_DELAY     100

Flashlight::Flashlight()
{
    frame_delay = 100;
}

void Flashlight::render()
{
    fill_solid(leds, NUM_LEDS, CRGB::White);
    FastLED.show();
}

Flashlight flashlight;
