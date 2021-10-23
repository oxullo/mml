#include <Arduino.h>


void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(BUTTON_BUILTIN, INPUT_PULLUP);
    SerialUSB.begin(9600);
}

void loop() 
{
    while (SerialUSB.available()) {
        SerialUSB.print("echo: ");
        SerialUSB.println(SerialUSB.read());
    }
    
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    if (digitalRead(BUTTON_BUILTIN)) {
        delay(100);
    } else {
        delay(20);
    }
}
