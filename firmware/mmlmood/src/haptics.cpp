#include <Arduino.h>
#include "haptics.h"

Haptics::Haptics()
{
}

void Haptics::begin()
{
    pinMode(HAPTIC_EN_PIN, OUTPUT);
    digitalWrite(HAPTIC_EN_PIN, HIGH);

    hardware.begin();
    hardware.selectLibrary(1);
    hardware.setMode(DRV2605_MODE_INTTRIG);
    hardware.setWaveform(0, 1);
    hardware.setWaveform(1, 0);
}

void Haptics::trigger(uint8_t waveform)
{
    hardware.go();
}

Haptics haptics;
