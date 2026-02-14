#ifndef DIGITAL_PIN_H
#define DIGITAL_PIN_H

#include <Arduino.h>

template<class T>
class DigitalPin{
protected:
    // pin number and mode (INPUT, OUTPUT, etc.)
    byte _pinNumber;
    byte _mode;

    // debounce variables for input pins
    unsigned long _debounceMs = 50;
    unsigned long _lastDebounceTime = 0;
    int _lastDebounceState = 0;

    // last stable value for input pins
    int _lastState = 0;
    
    void _updateAverage(int newValue) {
        // Shift readings to the left
        for (int i = 1; i < _numberOfReadings; i++) {
            _readings[i - 1] = _readings[i];
        }
        // Add new reading at the end
        _readings[_numberOfReadings - 1] = newValue;

        // Calculate average
        long sum = 0;
        for (int i = 0; i < _numberOfReadings; i++) {
            sum += _readings[i];
        }
        _averageValue = sum / _numberOfReadings;
    }


public:
    DigitalPin(byte pinNumber, byte mode) : _pinNumber(pinNumber), _mode(mode) {
        pinMode(_pinNumber, _mode);

        //initializing input pins with value LOW per default
        if(_mode != OUTPUT){
            _lastValue = LOW;
        }
    }

    //Update the output value of a digital pin
    void update(byte outputValue) {
        digitalWrite(_pinNumber, outputValue);
    }

    //Read value for digital pins having initialized with input modes
    void read() {
        _updateAverage(digitalRead(_pinNumber));

        if (_averageValue != _lastDebounceValue) {
            Serial.println("Value changed, starting debounce timer");
            _lastDebounceValue = _averageValue;
            _lastDebounceTime = millis();
        }

        if ((millis() - _lastDebounceTime) > _debounceMs) {
            if (_lastDebounceValue != _lastValue) {
                _lastValue = _averageValue;
            }
        }
    }

    //Retrieving value for input mode pins
    int getValue() {
        return _lastValue;
    }
};

#endif