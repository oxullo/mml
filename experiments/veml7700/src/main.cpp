#include <Arduino.h>
#include <Adafruit_VEML7700.h>

Adafruit_VEML7700 veml = Adafruit_VEML7700();

void setup() {
  while (!SerialUSB) { delay(10); }
  SerialUSB.begin(115200);
  SerialUSB.println("Adafruit VEML7700 Test");

  if (!veml.begin()) {
    SerialUSB.println("Sensor not found");
    while (1);
  }
  SerialUSB.println("Sensor found");

  veml.setGain(VEML7700_GAIN_1);
  veml.setIntegrationTime(VEML7700_IT_800MS);

  SerialUSB.print(F("Gain: "));
  switch (veml.getGain()) {
    case VEML7700_GAIN_1: SerialUSB.println("1"); break;
    case VEML7700_GAIN_2: SerialUSB.println("2"); break;
    case VEML7700_GAIN_1_4: SerialUSB.println("1/4"); break;
    case VEML7700_GAIN_1_8: SerialUSB.println("1/8"); break;
  }

  SerialUSB.print(F("Integration Time (ms): "));
  switch (veml.getIntegrationTime()) {
    case VEML7700_IT_25MS: SerialUSB.println("25"); break;
    case VEML7700_IT_50MS: SerialUSB.println("50"); break;
    case VEML7700_IT_100MS: SerialUSB.println("100"); break;
    case VEML7700_IT_200MS: SerialUSB.println("200"); break;
    case VEML7700_IT_400MS: SerialUSB.println("400"); break;
    case VEML7700_IT_800MS: SerialUSB.println("800"); break;
  }

  //veml.powerSaveEnable(true);
  //veml.setPowerSaveMode(VEML7700_POWERSAVE_MODE4);

  veml.setLowThreshold(10000);
  veml.setHighThreshold(20000);
  veml.interruptEnable(true);
}

void loop() {
  SerialUSB.print("Lux: "); SerialUSB.println(veml.readLux());
  SerialUSB.print("White: "); SerialUSB.println(veml.readWhite());
  SerialUSB.print("Raw ALS: "); SerialUSB.println(veml.readALS());

  uint16_t irq = veml.interruptStatus();
  if (irq & VEML7700_INTERRUPT_LOW) {
    SerialUSB.println("** Low threshold");
  }
  if (irq & VEML7700_INTERRUPT_HIGH) {
    SerialUSB.println("** High threshold");
  }
  delay(500);
}
