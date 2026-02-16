#ifndef ANALOG_PIN_H
#define ANALOG_PIN_H

#include <Arduino.h>

template<class A>
class AnalogPin{
    private:
    //Pin number and mode (INPUT, OUTPUT, etc.)
        byte _pinNumber;

        // debounce variables for input pins
        unsigned long _debounceMs = 50;
        unsigned long _lastDebounceTime = 0;
        int _debounceValue;

        //Reading avarage for smoothing out signal
        const static int _nrOfReadings = 5;
        int _readings[_nrOfReadings];
         int _averageValue;
        
        //Last stable state
        int _lastValue = 0;
       
    public:
        AnalogPin(byte pinNumber): _pinNumber(pinNumber){}
        
        void _updateAverage(int newValue) {
            // Shift readings to the left
            for (int i = 1; i < _nrOfReadings; i++) {
                _readings[i - 1] = _readings[i];
            }
            // Add new reading at the end
            _readings[_nrOfReadings - 1] = newValue;

            // Calculate average
            long sum = 0;
            for (int i = 0; i < _nrOfReadings; i++) {
                sum += _readings[i];
         }
        _averageValue = sum / _nrOfReadings;
        }

        void read(){
            int currentValue = analogRead(_pinNumber);

            if(currentValue != _debounceValue){
                _lastDebounceTime = millis();
                _debounceValue = currentValue;
            }

            if (millis() - _lastDebounceTime > _debounceMs){
                if (_debounceValue != _lastValue){
                    _lastValue = _debounceValue;
                }
            }
        }

        int getValue(){
            return _lastValue;
        }

        void resetValue(){
            _lastValue = 0;
        }
};

#endif

