#ifndef SRC_IMU_H_
#define SRC_IMU_H_

#include <stdint.h>

#include "LIS2DTW12.h"


class IMU {
public:
    static const uint8_t MAX_ORIENTATIONS = 7;

    typedef enum Orientation {
        ORIENTATION_UNKNOWN,
        ORIENTATION_VERTICAL_NORMAL,
        ORIENTATION_VERTICAL_90CW,
        ORIENTATION_VERTICAL_180,
        ORIENTATION_VERTICAL_90CCW,
        ORIENTATION_HORIZONTAL_TOP,
        ORIENTATION_HORIZONTAL_BOTTOM
    } Orientation;

    IMU();

    void begin();
    void update();

private:
    LIS2DTW12 accelerometer;
    uint16_t orientation_counters[MAX_ORIENTATIONS];

    void update_orientation();
};

#endif /* SRC_IMU_H_ */
