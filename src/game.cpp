#include <Arduino.h>
#include "game.h"

Game::Game(byte ledPins[], int nrOfLeds) {
  for (int c = 0; c < nrOfLeds ; c++) {
      Serial.println(ledPins[c]);
    _ledPins[c] = ledPins[c];
    pinMode(ledPins[c], OUTPUT);
  }
}

void Game::blinkLeds(int blinkRate) {
  for (int count = 0; count < 5; count++) {
    for (byte led : _ledPins) {
      digitalWrite(led, HIGH);
    }

    delay(blinkRate);

    for (byte led : _ledPins) {
      digitalWrite(led, LOW);
    }

    delay(blinkRate);
  }
}

void Game::randomLed() {
  _lastActiveLed = _ledPins[random(0, sizeof(_ledPins))];
  digitalWrite(_lastActiveLed, HIGH);
}

void Game::powerOffAllLeds() {
  for (byte led : _ledPins) {
    digitalWrite(led, LOW);
  }
}