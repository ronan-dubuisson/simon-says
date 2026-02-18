#include "Led.h"

Led::Led(byte pinNumber, LedLabels label) : DigitalPin(pinNumber, OUTPUT), _label(label) {}

LedLabels Led::getLabel(){
    return _label;
}