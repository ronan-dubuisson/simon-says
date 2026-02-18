#include "Led.h"

Led::Led(byte pinNumber, String label) : DigitalPin(pinNumber, OUTPUT), _label(label) {}

String Led::getLabel(){
    return _label;
}