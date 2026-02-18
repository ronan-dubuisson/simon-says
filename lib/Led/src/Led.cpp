#include "Led.h"

Led::Led(byte pinNumber, int id) : DigitalPin(pinNumber, OUTPUT), _id(id) {}