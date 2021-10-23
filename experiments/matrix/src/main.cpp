#include <Adafruit_NeoPixel.h>

#define PIN        2
#define NUMPIXELS 64

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
    pixels.begin();
}

void loop() {
    for(int i=0; i<NUMPIXELS; i++) {
        pixels.clear();
        pixels.setPixelColor(i, pixels.Color(255, 0, 0));
        pixels.show();

        delay(10);
    }
}
