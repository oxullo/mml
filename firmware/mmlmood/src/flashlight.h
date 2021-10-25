
#ifndef SRC_FLASHLIGHT_H_
#define SRC_FLASHLIGHT_H_

#include "animator.h"

class Flashlight : public Animator {
public:
    Flashlight();
    virtual void render();
};

extern Flashlight flashlight;


#endif /* SRC_FLASHLIGHT_H_ */
