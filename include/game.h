#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "sequence.h"

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
  void _powerOffAllLeds();
  void _toggleSingleLed(byte);
public:
  Game(byte[], int);
  
  void startNewGame();
  void resetGame();
  void newColorSequence();
 
  boolean isPlayerTurn();
  boolean isReset;
};

#endif