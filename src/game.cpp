#include "game.h"
#include "Led.h"

Game::Game(byte ledPins[]) :
  _leds{Led(ledPins[0]), Led(ledPins[1]), Led(ledPins[2]), Led(ledPins[3])}{}

/**
 * private method to blink all leds a certain amount of times for a visual effect at start or reset of the game
 */
void Game::_blinkLeds() {
  for (int count = 0; count < 5; count++) {
    for (Led led : _leds) {
      led.update(HIGH);
    }

    delay(_blinkInterval);

    for (Led led : _leds) {
      led.update(LOW);
    }

    delay(_blinkInterval);
  }
}

/**
  * public method to toggle a single led for a set time
  */
void Game::_toggleSingleLed(byte ledPin) {
  digitalWrite(ledPin, HIGH);
  delay(_sequenceDuration);
  digitalWrite(ledPin, LOW);
}

/**
 * public method to power off all leds in case of reset or end of game
 */
void Game::_powerOffAllLeds() {
  for (Led led : _leds) {
    led.update(LOW);
  }
}

/**
 * public method to start a new game
 */
void Game::startNewGame() {
  _blinkLeds();
  delay(_waitStartInterval);
  _isPlayerTurn = false;
}

/**
 * public method to reset the game
 */
void Game::resetGame() {
  _sequenceArray = SequenceArray(); // Reset the sequence array
  _powerOffAllLeds();
  startNewGame();
  isReset = false;
}

/**
 * public method to start a new color sequence
 */
void Game::newColorSequence() {
   _sequenceArray.addToSequence((byte)random(0,4));
   _toggleSingleLed(_sequenceArray.getLastElement());
   _isPlayerTurn = true;
}

/**
 * public method to check if it's the player's turn
 */
boolean Game::isPlayerTurn() {
  return _isPlayerTurn;
}