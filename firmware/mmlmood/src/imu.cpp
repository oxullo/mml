
#include <Arduino.h>

#include "imu.h"


IMU::IMU() :
    tilt_threshold_min(0),
    tilt_threshold_max(0),
    last_orientation(IMU::ORIENTATION_UNKNOWN)
{
}


void IMU::begin(uint16_t tilt_threshold_min, uint16_t tilt_threshold_max)
{
    this->tilt_threshold_min = tilt_threshold_min;
    this->tilt_threshold_max = tilt_threshold_max;
    accelerometer.begin();
}

// Returns ORIENTATION_UNKNOWN when no orientation change is detected
IMU::Orientation IMU::update()
{
    if (accelerometer.is_data_ready()) {
        accelerometer.read();
        IMU::Orientation current_orientation = evaluate_orientation();

        if (current_orientation != IMU::ORIENTATION_UNKNOWN &&
                current_orientation != last_orientation) {
            last_orientation = current_orientation;

            return current_orientation;
        }
    }

    return IMU::ORIENTATION_UNKNOWN;
}

IMU::Orientation IMU::evaluate_orientation()
{
    IMU::Orientation candidate = IMU::ORIENTATION_UNKNOWN;

    if (abs(accelerometer.mg().z) < tilt_threshold_min) {
        if (abs(accelerometer.mg().x) < tilt_threshold_min) {
            if (accelerometer.mg().y > tilt_threshold_max) {
                candidate = IMU::ORIENTATION_VERTICAL_NORMAL;
            } else if (accelerometer.mg().y < -tilt_threshold_max) {
                candidate = IMU::ORIENTATION_VERTICAL_180;
            }
        } else if (abs(accelerometer.mg().y) < tilt_threshold_min) {
            if (accelerometer.mg().x > tilt_threshold_max) {
                candidate = IMU::ORIENTATION_VERTICAL_90CW;
            } else if (accelerometer.mg().x < -tilt_threshold_max) {
                candidate = IMU::ORIENTATION_VERTICAL_90CCW;
            }
        }
    } else {
        if (accelerometer.mg().z > tilt_threshold_max) {
            candidate = IMU::ORIENTATION_HORIZONTAL_BOTTOM;
        } else if (accelerometer.mg().z < -tilt_threshold_max) {
            candidate = IMU::ORIENTATION_HORIZONTAL_TOP;
        }
    }

    if (orientation_counters[candidate] < COUNT_THRESHOLD + COUNT_HYSTERESIS) {
        ++orientation_counters[candidate];
    }

    IMU::Orientation detected = IMU::ORIENTATION_UNKNOWN;
    for (uint8_t i=0 ; i < IMU::MAX_ORIENTATIONS ; ++i) {
        if (i != candidate && orientation_counters[i] != 0) {
            --orientation_counters[i];
        }

        // TODO: invalidate when more than one counter asserts
        if (orientation_counters[i] > COUNT_THRESHOLD) {
            detected = (IMU::Orientation)i;
        }
    }

    return detected;
}
