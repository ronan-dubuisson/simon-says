#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "sequence/sequence.h"
#include "Led.h"
#include "VoltageDividerInputDetection.h"

class Game {
private:
  SequenceArray _sequenceArray;
  const int _sequenceDuration = 1000;
  const int _blinkInterval = 70;
  const int _waitStartInterval = 2000;

  Led _leds[4];

  void _blinkLeds();
  void _powerOffAllLeds();
  void _toggleSingleLed(byte);
public:
  Game(byte[], byte);

  VoltageDividerInputDetection _playerInput;
  
  void startNewGame();
  void resetGame();
  void newColorSequence();
  bool verifySequence(String pressedButton);

  boolean isReset;
};

#endif