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
 * private method to power on a random led for a set time for a new sequence
 */
void Game::_randomLed() {
  //TODO: Return the random led to be stored, powering on of the led will be handled by another function
  _lastActiveLed = _ledPins[random(0, sizeof(_ledPins))];
  toggleSingleLed(_lastActiveLed);
}

/**
 * public method to start a new color sequence
 */
void Game::newColorSequence() {
   //TODO: store old array in new array length +1 and add new sequence to array

  //power an lastActiveLed for a set time and then power it off for a new sequence
  _randomLed();
}

void Game::toggleSingleLed(byte ledPin) {
  digitalWrite(ledPin, HIGH);
  delay(_sequenceOnTime);
  digitalWrite(ledPin, LOW);
}

/**
 * public method to blink all leds a certain amount of times for a visual effect at start or reset of the game
 */
void Game::blinkLeds() {
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
 * public method to power off all leds in case of reset or end of game
 */
void Game::powerOffAllLeds() {
  for (byte led : _ledPins) {
    digitalWrite(led, LOW);
  }
}