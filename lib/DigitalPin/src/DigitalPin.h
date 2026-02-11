#ifndef DIGITAL_PIN_H
#define DIGITAL_PIN_H

#include <Arduino.h>

template<class T>
class DigitalPin{
protected:
    byte _pinNumber;
    byte _mode;
public:
    DigitalPin(byte pinNumber, byte mode) : _pinNumber(pinNumber), _mode(mode) {
        pinMode(_pinNumber, _mode);
    }

    void update(byte outputValue) {
        digitalWrite(_pinNumber, outputValue);
    }
};

#endif