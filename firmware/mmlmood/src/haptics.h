
#ifndef SRC_HAPTICS_H_
#define SRC_HAPTICS_H_

#include <Adafruit_DRV2605.h>

class Haptics {
public:
    Haptics();

    void begin();
    void trigger(uint8_t waveform = 1);

private:
    Adafruit_DRV2605 hardware;

};

extern Haptics haptics;

#endif /* SRC_HAPTICS_H_ */
