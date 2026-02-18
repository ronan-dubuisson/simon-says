#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <Arduino.h>
#include "DigitalPin.h"

class PushButton : public DigitalPin<PushButton>{
    public:
        PushButton(byte, String);
        
    private:
        bool _lastState;
        String _label;

};

#endif