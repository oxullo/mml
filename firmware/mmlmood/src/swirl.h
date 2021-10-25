
#ifndef SRC_SWIRL_H_
#define SRC_SWIRL_H_

#include "animator.h"

class Swirl : public Animator {
public:
    Swirl();
    virtual void render();
};

extern Swirl swirl;


#endif /* SRC_SWIRL_H_ */
