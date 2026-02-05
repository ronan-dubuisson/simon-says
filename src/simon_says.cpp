#include "game.h"

// pin assignments
byte ledPins[4] = { 4, 5, 6, 7};
byte resetBtn = 2; //5 seconds reset wait time

//initialize game object
Game simon(ledPins, sizeof(ledPins));

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(resetBtn), [](){
    // Interrupt service routine for reset button
    simon.isReset = true;
  }, HIGH);

  simon.startNewGame();
}

void loop() {
  // put your main code here, to run repeatedly:

  if (simon.isReset) {
    simon.resetGame();
  }

  if (!simon.isPlayerTurn()) {
    simon.newColorSequence();
  }
}