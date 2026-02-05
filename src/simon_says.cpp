#include "game.h"

// pin assignments
byte ledPins[4] = { 2, 3, 4, 5 };
byte resetBtn = A1; //5 seconds reset wait time

//initialize game object
Game simon(ledPins, sizeof(ledPins));

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(resetBtn,INPUT_PULLUP);
  simon.startNewGame();
}

void loop() {
  // put your main code here, to run repeatedly:

  if (analogRead(resetBtn) == 1023) {
    Serial.println(analogRead(resetBtn));
    simon.resetGame();
  }

  if (!simon.isPlayerTurn()) {
    simon.newColorSequence();
  }
}