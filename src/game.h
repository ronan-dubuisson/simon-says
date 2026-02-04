#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "helpers/sequence.h"

class Game {
private:
  SequenceArray _sequenceArray;
  const int _sequenceDuration = 1000;
  const int _blinkInterval = 250;
  const int _waitStartInterval = 2000;

  byte _ledPins[4];
  boolean _isPlayerTurn = false;

  byte _randomLed();
  void _blinkLeds();
public:
  Game(byte[], int);
  
  void startNewGame();
  void newColorSequence();
  void toggleSingleLed(byte);
  void powerOffAllLeds();
  boolean isPlayerTurn();
};

#endif