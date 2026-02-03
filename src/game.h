#ifndef GAME_H
#define GAME_H

#include <Arduino.h>

class Game {
private:
  byte _ledPins[4];
  byte _lastActiveLed;
public:
  Game(byte[], int);
  void blinkLeds(int blinkRate);
  void randomLed();
  void powerOffAllLeds();
};

#endif