#ifndef SRC_IMU_H_
#define SRC_IMU_H_

#include <stdint.h>

#include "LIS2DTW12.h"


class IMU {
public:
    static const uint8_t MAX_ORIENTATIONS = 7;
    // TODO: time-invariant (in respect to ODR)
    const uint16_t COUNT_THRESHOLD = 200;
    const uint16_t COUNT_HYSTERESIS = 100;

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

    void begin(float tilt_threshold_min, float tilt_threshold_max);
    Orientation update();

    Orientation get_orientation() const
    {
        return last_orientation;
    }

    LIS2DTW12::AccelData mg() const
    {
        return accelerometer.mg();
    }
    LIS2DTW12::AccelData norm() const
    {
        return accelerometer.norm();
    }

private:
    LIS2DTW12 accelerometer;
    uint16_t orientation_counters[MAX_ORIENTATIONS];
    float tilt_threshold_min;
    float tilt_threshold_max;
    Orientation last_orientation;

    IMU::Orientation evaluate_orientation();
};

extern IMU imu;

#endif /* SRC_IMU_H_ */
