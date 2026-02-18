#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include "DigitalPin.h"
#include "enums/ledLabels.h"

class Led : public DigitalPin<Led>{
    public:
        Led(byte, LedLabels);
        LedLabels getLabel();
    private:
        LedLabels _label;
};


#endif