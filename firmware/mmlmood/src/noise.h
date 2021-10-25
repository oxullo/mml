
#ifndef SRC_NOISE_H_
#define SRC_NOISE_H_

#include <stdint.h>

#include "matrix.h"
#include "animator.h"

class Noise : public Animator {
public:
    Noise();
    virtual void reset();
    virtual void render();

private:
    uint16_t speed;
    uint16_t scale;

    uint8_t noisemap[MAX_DIMENSION][MAX_DIMENSION];
    uint16_t x;
    uint16_t y;
    uint16_t z;
};

extern Noise noise;


#endif /* SRC_NOISE_H_ */
