#ifndef POWER_FUNCTIONS_HPP
#define POWER_FUNCTIONS_HPP

#include <Arduino.h>
#include "ioPins.h"

void powerOn() { 
    digitalWrite(PIN_POWER_UP, HIGH);
}

void powerInit() {
    pinMode(PIN_POWER_UP, OUTPUT);
    powerOn();
}

void powerOff() {
    digitalWrite(PIN_POWER_UP, LOW);
}

#endif // POWER_FUNCTIONS_HPP
