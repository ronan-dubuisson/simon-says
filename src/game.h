#ifndef GAME_H
#define GAME_H

#include <Arduino.h>

class Game {
private:
  const int _sequenceOnTime = 500;
  const int _blinkInterval = 250;

  byte _ledPins[4];
  byte _lastActiveLed;
  int sequence[];

  void _randomLed();
public:
  Game(byte[], int);
  
  void newColorSequence();
  void blinkLeds();
  void toggleSingleLed(byte);
  void powerOffAllLeds();
};

#endif