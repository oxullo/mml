/*
 * LIS2DTW12.cpp
 *
 *  Created on: Oct 18, 2021
 *      Author: xi
 */

// Driver: https://github.com/STMicroelectronics/lis2dtw12
// Examples: https://github.com/STMicroelectronics/STMems_Standard_C_drivers/tree/master/lis2dtw12_STdC/examples


#include "LIS2DTW12.h"

LIS2DTW12::LIS2DTW12() :
    address(0),
    wire_port(NULL),
    data_raw_temperature(0),
    temperature(0)
{
}

bool LIS2DTW12::begin(uint8_t address, TwoWire& wire_port)
{
    this->address = address;
    this->wire_port = &wire_port;

    dev_ctx.write_reg = platform_write;
    dev_ctx.read_reg = platform_read;
    dev_ctx.handle = (void*)this;

    if (!test_unit()) {
        return false;
    }

    // Restore default configuration
    lis2dtw12_reset_set(&dev_ctx, PROPERTY_ENABLE);

    // Wait until reset is acknowledged
    uint8_t rst;
    do {
      lis2dtw12_reset_get(&dev_ctx, &rst);
    } while (rst);

    //Enable Block Data Update
    lis2dtw12_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);

    lis2dtw12_data_rate_set(&dev_ctx, LIS2DTW12_XL_ODR_25Hz);
    lis2dtw12_full_scale_set(&dev_ctx, LIS2DTW12_2g);
    lis2dtw12_power_mode_set(&dev_ctx, LIS2DTW12_CONT_LOW_PWR_LOW_NOISE_12bit);

    return true;
}

int32_t LIS2DTW12::platform_write(void *handle, uint8_t reg, const uint8_t *bufp,
        uint16_t len)
{
    LIS2DTW12 *this_handle = (LIS2DTW12*) handle;

    if (len > 30) {
        return 1; // Error
    }

    this_handle->wire_port->beginTransmission(this_handle->address);
    this_handle->wire_port->write(reg);
    for (uint16_t x = 0; x < len; x++) {
        this_handle->wire_port->write(bufp[x]);
    }

    byte end = this_handle->wire_port->endTransmission();

    return end; // Will return 0 upon success
}

int32_t LIS2DTW12::platform_read(void *handle, uint8_t reg, uint8_t *bufp,
        uint16_t len)
{
    LIS2DTW12 *this_handle = (LIS2DTW12*) handle;

    if (len > 1) {
        // For multi byte reads we must set the first bit to 1
        reg |= 0x80;
    }

    this_handle->wire_port->beginTransmission(this_handle->address);
    this_handle->wire_port->write(reg);
    this_handle->wire_port->endTransmission(false); // Don't release the bus. Will return 0 upon success.

    this_handle->wire_port->requestFrom((uint8_t) this_handle->address,
            (uint8_t) len);
    for (uint16_t x = 0; x < len; x++) {
        bufp[x] = this_handle->wire_port->read();
    }

    return 0; // Success
}

bool LIS2DTW12::is_data_ready()
{
    uint8_t reg;
    lis2dtw12_flag_data_ready_get(&dev_ctx, &reg);

    return (bool)reg;
}

void LIS2DTW12::read()
{
    // Expects is_data_ready() to be tested true

    memset(data_raw_acceleration, 0x00, 3 * sizeof(int16_t));

    lis2dtw12_acceleration_raw_get(&dev_ctx, data_raw_acceleration);
    accel_mg_data.x = lis2dtw12_from_fs8_lp1_to_mg(data_raw_acceleration[0]);
    accel_mg_data.y = lis2dtw12_from_fs8_lp1_to_mg(data_raw_acceleration[1]);
    accel_mg_data.z = lis2dtw12_from_fs8_lp1_to_mg(data_raw_acceleration[2]);

    memset(&data_raw_temperature, 0x00, sizeof(int16_t));
    lis2dtw12_temperature_raw_get(&dev_ctx, &data_raw_temperature);
    temperature = lis2dtw12_from_lsb_to_celsius(data_raw_temperature);
}

bool LIS2DTW12::test_unit()
{
    wire_port->beginTransmission(address);

    if (wire_port->endTransmission() == 0) {
        // Something ack'd at this address. Check ID.
        uint8_t whoami;

        lis2dtw12_device_id_get(&dev_ctx, &whoami);

        return whoami == LIS2DTW12_ID;
    } else {
        return false;
    }
}
