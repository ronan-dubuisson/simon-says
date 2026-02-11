#include <Arduino.h>
#include "game.h"

// pin assignments
byte ledPins[4] = { 4, 5, 6, 7};
byte resetBtn = 2; //5 seconds reset wait time

//initialize game object
Game simon(ledPins);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(resetBtn), [](){
    // Interrupt service routine for reset button
    simon.isReset = true;
  }, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

  switch(simon.currentState) {
    case Game::START:
      simon.startNewGame();
      break;
    case Game::PLAYER_TURN:
    break;
    case Game::COMPUTER_TURN:
        simon.newColorSequence();
        simon.currentState = Game::PLAYER_TURN;
      break;
    case Game::END:
    break;
  }
}