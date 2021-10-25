/*
 * LIS2DTW12.h
 *
 *  Created on: Oct 18, 2021
 *      Author: xi
 */

#ifndef SRC_LIS2DTW12_H_
#define SRC_LIS2DTW12_H_

#include <Arduino.h>
#include <Wire.h>

#include "lis2dtw12_reg.h"

typedef struct AccelData {
    float x, y, z;
} AccelData;

class LIS2DTW12 {
public:
    static const uint8_t DEFAULT_ADDRESS = 0x18;

    LIS2DTW12();

    bool begin(uint8_t address = DEFAULT_ADDRESS, TwoWire &wire_port = Wire);
    bool is_data_ready();
    void read();

    const AccelData& mg() const
    {
        return accel_mg_data;
    }

private:
    uint8_t address;
    TwoWire* wire_port;
    stmdev_ctx_t dev_ctx;
    int16_t data_raw_acceleration[3];
    int16_t data_raw_temperature;
    AccelData accel_mg_data;
    float temperature;
    uint8_t multiplier;

    static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp, uint16_t len);
    static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);

    bool test_unit();
};

#endif /* SRC_LIS2DTW12_H_ */
