
#include <Arduino.h>

#include "imu.h"


IMU::IMU()
{
}


void IMU::begin()
{
    accelerometer.begin();
}

void IMU::update()
{
    if (accelerometer.is_data_ready()) {
        accelerometer.read();
        update_orientation();

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

void IMU::update_orientation()
{
    const uint16_t TILT_THRESHOLD_MIN = 2000;
    const uint16_t TILT_THRESHOLD_MAX = 7500;

    IMU::Orientation candidate = IMU::ORIENTATION_UNKNOWN;

    if (abs(accelerometer.mg().z) < TILT_THRESHOLD_MIN) {
        if (abs(accelerometer.mg().x) < TILT_THRESHOLD_MIN) {
            if (accelerometer.mg().y > TILT_THRESHOLD_MAX) {
                candidate = IMU::ORIENTATION_VERTICAL_NORMAL;
            } else if (accelerometer.mg().y < -TILT_THRESHOLD_MAX) {
                candidate = IMU::ORIENTATION_VERTICAL_180;
            }
        } else if (abs(accelerometer.mg().y) < TILT_THRESHOLD_MIN) {
            if (accelerometer.mg().x > TILT_THRESHOLD_MAX) {
                candidate = IMU::ORIENTATION_VERTICAL_90CW;
            } else if (accelerometer.mg().x < -TILT_THRESHOLD_MAX) {
                candidate = IMU::ORIENTATION_VERTICAL_90CCW;
            }
        }
    } else {
        if (accelerometer.mg().z > TILT_THRESHOLD_MAX) {
            candidate = IMU::ORIENTATION_HORIZONTAL_BOTTOM;
        } else if (accelerometer.mg().z < -TILT_THRESHOLD_MAX) {
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
