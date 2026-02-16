#include "VoltageDividerInputDetection.h"

VoltageDividerInputDetection::VoltageDividerInputDetection(byte analogInput, int pullDownResistor, int *dividerResistors, int nrOfButtons):
_analogInput(analogInput),
_pullDownResistorValue (pullDownResistor),
_dividerResistorValues(dividerResistors),
_nrOfButtons(nrOfButtons)
{

    _buttons = new Buttons[nrOfButtons];
    //0 - 1023 analog input read range
    //R2 = target resistor
    //Rg = pull down resistor
    //R2/(R2+R1)

    _buttons[0].label = "RED";
    _buttons[0].upperThresholdValue = 1023;
    _buttons[0].lowerThresholdValue = 1023 - _threshold;

    _buttons[1].label = "GREEN";
    _buttons[2].label = "YELLOW";
    _buttons[3].label = "BLUE";

    double R2; // storing the increasing resistance for voltage drop calculation

    for (int i = 0; i < _nrOfButtons - 1 ; i++){
        R2 += *_dividerResistorValues++;
        double idealValue = 1023 * (1 - (R2 / (R2 + _pullDownResistorValue)));
        
        _buttons[i + 1].upperThresholdValue = (int) (idealValue + _threshold);
        _buttons[i + 1].lowerThresholdValue = (int) (idealValue - _threshold);
    }
}

void VoltageDividerInputDetection::read(){
    int currentValue = analogRead(_analogInput);

    for (int i = 0; i < _nrOfButtons; i++){
        Buttons button = _buttons[i];
        if(currentValue >= button.lowerThresholdValue && currentValue <= button.upperThresholdValue){
            _lastPressedButton = i;
            Serial.print("Button: ");
            Serial.print(button.label);
            Serial.println(" has been pressed!");
            break;
        }
    }
}

/** Printer thresholdvalues for the buttons in the voltage divider for testing purposes */
void VoltageDividerInputDetection::printDividerRes(){

        Serial.println(analogRead(_analogInput));
        Serial.println(_nrOfButtons);
   
       for(int i=0; i < _nrOfButtons; i++){
        Serial.print(_buttons[i].label);
        Serial.print(" ; ");
        Serial.print(_buttons[i].upperThresholdValue);
        Serial.print(" ; ");
        Serial.println(_buttons[i].lowerThresholdValue);
       }
    
}