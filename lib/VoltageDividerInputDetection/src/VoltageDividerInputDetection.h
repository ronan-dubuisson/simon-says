#ifndef VOLTAGE_DIVIDER_INPUT_DETECTION_H
#define VOLTAGE_DIVIDER_INPUT_DETECTION_H

#include <Arduino.h>
#include "PushButton.h"
#include "Led.h"

struct Button {
  String label;
  int lowerThresholdValue;
  int upperThresholdValue;
};

//TODO: Write VoltageDivider Logic on button press detection
//Generic class that is initialize with different amount of buttons provided at initialization
class VoltageDividerInputDetection {
  private:
    byte _analogInput;
    int _pullDownResistorValue;
    int *_dividerResistorValues;
    const double _threshold = 50; //Threshold for range of values to take into account fluctuation on vOut.
    int _nrOfButtons;
    Button *_buttons;
    Button _lastPressedButton;
    bool _hasInput = false;
    Led *_leds;

  public:
    VoltageDividerInputDetection(byte, int, int*, int);
    void read();
    bool hasInput();
    Button getPressedButton();
    void printDividerRes();
   
};

#endif