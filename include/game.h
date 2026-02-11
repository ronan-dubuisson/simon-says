#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "sequence.h"
#include "Led.h"

class Game {
private:
  SequenceArray _sequenceArray;
  const int _sequenceDuration = 1000;
  const int _blinkInterval = 250;
  const int _waitStartInterval = 2000;

  Led _leds[4];
  boolean _isPlayerTurn;

  void _blinkLeds();
  void _powerOffAllLeds();
  void _toggleSingleLed(byte);
public:
  Game(byte[]);
  
  void startNewGame();
  void resetGame();
  void newColorSequence();
 
  boolean isPlayerTurn();
  boolean isReset;
};

#endif