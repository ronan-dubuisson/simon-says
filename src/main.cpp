#include <Arduino.h>
#include "game.h"
#include "VoltageDividerInputDetection.h"

// pin assignments
byte playerInputPin = A0;
byte ledPins[4] = { 4, 5, 6, 7};
byte resetBtn = 2; //5 seconds reset wait time

//voltageDivider transistors
int pullDownResistor = 10000;

//initialize libraries
Game simon(ledPins, playerInputPin);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // attachInterrupt(digitalPinToInterrupt(resetBtn), [](){
  //   // Interrupt service routine for reset button
  //   simon.currentState = Game::START;
  // }, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

  switch(simon.currentState) {
    case Game::START:
    Serial.println("Start Game");
      simon.startNewGame();
      simon.currentState = Game::COMPUTER_TURN;
      break;
    case Game::PLAYER_TURN:
      simon._playerInput.read();
    break;
    case Game::COMPUTER_TURN:
        simon.newColorSequence();
        simon.currentState = Game::PLAYER_TURN;
      break;
    case Game::END:
    break;
  }
}