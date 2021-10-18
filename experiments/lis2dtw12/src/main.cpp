#include <Arduino.h>

#include "LIS2DTW12.h"

LIS2DTW12 accel;

void setup()
{
    accel.begin();
}

void loop()
{
    if (accel.is_data_ready()) {
        accel.read();

        Serial.print("x=");
        Serial.print(accel.mg().x);
        Serial.print(" y=");
        Serial.print(accel.mg().y);
        Serial.print(" z=");
        Serial.println(accel.mg().z);
    }
}
