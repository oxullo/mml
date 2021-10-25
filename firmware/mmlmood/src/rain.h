
#ifndef SRC_RAIN_H_
#define SRC_RAIN_H_

#include "animator.h"

#define MAX_DROPS       6


class Drop {
public:
    Drop();
    bool is_alive();
    void reset();
    void start();
    void step();
    uint8_t get_x();
    uint8_t get_y();

private:
    bool alive;
    float x;
    float y;
    float friction;
};

class Rain : public Animator {
public:
    Rain();
    virtual void reset();
    virtual void render();

private:
    Drop drops[MAX_DROPS];
};

extern Rain rain;


#endif /* SRC_RAIN_H_ */
