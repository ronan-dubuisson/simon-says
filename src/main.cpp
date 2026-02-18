//#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "VoltageDividerInputDetection.h"
#include "enums/game.h"
#include "Led.h"
#include "PushButton.h"
#include "enums/ledLabels.h"

// OLED display configuration
const int SCREEN_WIDTH = 128 ;// OLED display width, in pixels
const int SCREEN_HEIGHT = 64 ;// OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // -1 means no reset pin

Led leds[4] = {
  Led(4, LedLabels::RED),
  Led(5, LedLabels::GREEN),
  Led(6, LedLabels::BLUE),
  Led(7, LedLabels::YELLOW)
};

PushButton resetButton(2, "Reset button");

//voltage divider load resistors for player input detection
int dividerResistors[] = {3000, 6800, 22000};
VoltageDividerInputDetection vd(A0, 10000, dividerResistors, sizeof(dividerResistors) / sizeof(dividerResistors[0]) + 1);


States state;

//voltageDivider transistors
int pullDownResistor = 10000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  state = States::START_UP;

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

  switch(state) {
    case States::START_UP:
      simon.startNewGame();
      state = States::COMPUTER_TURN;
      break;
    case States::PLAYER_TURN:
      simon._playerInput.read();
    break;
    case States::COMPUTER_TURN:
        simon.newColorSequence();
        state = States::PLAYER_TURN;
    case States::END_GAME:
      simon.resetGame();
    break;
  }
}