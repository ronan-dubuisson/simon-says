#ifndef DIGITAL_PIN_H
#define DIGITAL_PIN_H

#include <Arduino.h>

template<class T>
class DigitalPin{
protected:
    // pin number and mode (INPUT, OUTPUT, etc.)
    uint8_t _pinNumber;
    byte _mode;

    // debounce variables for input pins
    unsigned long _debounceMs = 50;
    unsigned long _lastDebounceTime = 0;
    int _lastDebounceState = 0;

    // last stable value for input pins
    int _lastState = 0;
    

public:
    DigitalPin(byte pinNumber, byte mode) : _pinNumber(pinNumber), _mode(mode) {
        pinMode(_pinNumber, _mode);

        //initializing input pins with value LOW per default
        if(_mode != OUTPUT){
            _lastState = LOW;
        }
    }

    //Update the output value of a digital pin
    void update(byte outputValue) {
        digitalWrite(_pinNumber, outputValue);
    }

    //Read value for digital pins having initialized with input modes
    void read() {
        byte currentState = (digitalRead(_pinNumber));

        if (currentState != _lastDebounceState) {
            Serial.println("Value changed, starting debounce timer");
            _lastDebounceState = currentState;
            _lastDebounceTime = millis();
        }

        if ((millis() - _lastDebounceTime) > _debounceMs) {
            if (_lastDebounceState != _lastState) {
                _lastState = _lastDebounceState;
            }
        }
    }

    //Retrieving value for input mode pins
    int getValue() {
        return _lastState;
    }
};

#endif