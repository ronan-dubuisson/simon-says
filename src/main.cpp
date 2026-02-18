//#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "game.h"
#include "VoltageDividerInputDetection.h"
#include "States.h"

const int SCREEN_WIDTH = 128 ;// OLED display width, in pixels
const int SCREEN_HEIGHT = 64 ;// OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // -1 means no reset pin

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
  static States state = States::START_UP;

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // 0x3C is common I2C address
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
 
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 30);
  display.println("SIMON SAYS");
  display.display();  // Actually push data to the screen


  // attachInterrupt(digitalPinToInterrupt(resetBtn), [](){
  //   // Interrupt service routine for reset button
  //   simon.currentState = Game::START;
  // }, HIGH);
}


void loop() {

  // put your main code here, to run repeatedly:

  switch(simon.currentState) {
    case Game::START:
      simon.startNewGame();
      simon.currentState = Game::COMPUTER_TURN;
      break;
    // case Game::PLAYER_TURN:
    //   simon._playerInput.read();
    // break;
    // case Game::COMPUTER_TURN:
    //     simon.newColorSequence();
    //     simon.currentState = Game::PLAYER_TURN;
    //   break;
    // case Game::END:
    break;
  }
}