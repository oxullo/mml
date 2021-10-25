
#include <Arduino.h>

#include "imu.h"


IMU::IMU() :
    tilt_threshold_min(0),
    tilt_threshold_max(0)
{
}


void IMU::begin(uint16_t tilt_threshold_min, uint16_t tilt_threshold_max)
{
    this->tilt_threshold_min = tilt_threshold_min;
    this->tilt_threshold_max = tilt_threshold_max;
    accelerometer.begin();
}

void IMU::update()
{
    if (accelerometer.is_data_ready()) {
        accelerometer.read();
        evaluate_orientation();

//        Serial.print(accelerometer.mg().x);
//        Serial.print(" ");
//        Serial.print(accelerometer.mg().y);
//        Serial.print(" ");
//        Serial.println(accelerometer.mg().z);

        for (uint8_t i=0 ; i < IMU::MAX_ORIENTATIONS ; ++i) {
            if (orientation_counters[i] > 200) {
                Serial.println(i);
            }
        }
    }
}

void IMU::evaluate_orientation()
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

    if (orientation_counters[candidate] < 300) {
        ++orientation_counters[candidate];
    }

    for (uint8_t i=0 ; i < IMU::MAX_ORIENTATIONS ; ++i) {
        if (i != candidate && orientation_counters[i] != 0) {
            --orientation_counters[i];
        }
    }
}
