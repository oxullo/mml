
#ifndef SRC_CONFETTI_H_
#define SRC_CONFETTI_H_

#include <stdint.h>

#include "animator.h"

class Confetti : public Animator {
public:
    Confetti();
    virtual void render();

private:
    uint8_t hue;
    uint8_t probability;
};

extern Confetti confetti;


#endif /* SRC_CONFETTI_H_ */
