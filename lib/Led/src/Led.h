#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include "DigitalPin.h"

class Led : public DigitalPin<Led>{
    public:
        Led(byte, String);
        String getLabel();
    private:
        String _label;
};


#endif