#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include "DigitalPin.h"

class Led : public DigitalPin<Led>{
    public:
        Led(byte, int);
    private:
        int _id;
};


#endif