#include "PushButton.h"

PushButton::PushButton(byte pinNumber, String label) : _label(label), DigitalPin(pinNumber, INPUT){}