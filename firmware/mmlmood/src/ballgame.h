#ifndef BALLGAME_H
#define BALLGAME_H

#include "animator.h"

class Ballgame : public Animator {
public:
    Ballgame();
    virtual void reset();
    virtual void render();

private:
    float vx;
    float vy;
    float ballx;
    float bally;
};

extern Ballgame ballgame;

#endif
