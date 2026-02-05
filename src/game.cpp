#include <Arduino.h>
#include "game.h"

Game::Game(byte ledPins[], int nrOfLeds) {
  for (int c = 0; c < nrOfLeds ; c++) {
      Serial.println(ledPins[c]);
    _ledPins[c] = ledPins[c];
    pinMode(ledPins[c], OUTPUT);
  }  
}

/**
 * private method to blink all leds a certain amount of times for a visual effect at start or reset of the game
 */
void Game::_blinkLeds() {
  for (int count = 0; count < 5; count++) {
    for (byte led : _ledPins) {
      digitalWrite(led, HIGH);
    }

    delay(_blinkInterval);

    for (byte led : _ledPins) {
      digitalWrite(led, LOW);
    }

    delay(_blinkInterval);
  }
}

/**
 * private method to power on a random led for a set time for a new sequence
 */
byte Game::_randomLed() {
  //TODO: Return the random led to be stored, powering on of the led will be handled by another function
  return _ledPins[random(0, sizeof(_ledPins))];
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
  for (byte led : _ledPins) {
    digitalWrite(led, LOW);
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
   _sequenceArray.addToSequence(_randomLed());
   _toggleSingleLed(_sequenceArray.getLastElement());
   _isPlayerTurn = true;
}

/**
 * public method to check if it's the player's turn
 */
boolean Game::isPlayerTurn() {
  return _isPlayerTurn;
}