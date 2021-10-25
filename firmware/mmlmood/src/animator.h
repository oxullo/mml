
#ifndef SRC_ANIMATOR_H_
#define SRC_ANIMATOR_H_

#define DEFAULT_ANIMATOR_FRAME_DELAY        16

class Animator {
public:
    Animator() {};
    virtual ~Animator() {};
    virtual void reset() {};
    virtual void render() = 0;

    uint8_t frame_delay = DEFAULT_ANIMATOR_FRAME_DELAY;
};

#endif /* SRC_ANIMATOR_H_ */
