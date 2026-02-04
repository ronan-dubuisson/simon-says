#include "game.h"

byte activeLed = 0;
byte ledPins[4] = { 2, 3, 4, 5 };
byte resetBtn = A1;
int resetTime = 5000;  //5 seconds reset wait time
unsigned long lastReset = resetTime * -1;
unsigned long lastActive = 0;

int timeout = 500;
Game simon(ledPins, sizeof(ledPins));

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(resetBtn,INPUT_PULLUP);
  simon.blinkLeds();
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (analogRead(resetBtn) == 1023) {
    Serial.println(analogRead(resetBtn));
    lastReset = millis();
    simon.powerOffAllLeds();
  }

  if (millis() - lastReset > resetTime && millis() - lastActive > timeout) {
    lastActive = millis();
    simon.newColorSequence();
  }
}