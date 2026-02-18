#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include "VoltageDividerInputDetection.h"
#include "enums/game.h"
#include "Led.h"
#include "PushButton.h"
#include "enums/ledLabels.h"

Adafruit_SSD1306 display(128, 64, &Wire, -1); // Initialize display with width, height

Led leds[4] = {
  Led(4, (int) LedLabels::RED),
  Led(5, (int) LedLabels::GREEN),
  Led(6, (int)LedLabels::YELLOW),
  Led(7, (int) LedLabels::BLUE)
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
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // attachInterrupt(digitalPinToInterrupt(resetBtn), [](){
  //   // Interrupt service routine for reset button
  //   simon.currentState = Game::START;
  // }, HIGH);
}


void loop() {

  // put your main code here, to run repeatedly:

  switch(state) {
    case States::START_UP:
      display.setCursor(0, 15);
      display.println("Simon Says");
      display.display();
      // Start dimming the display
     // Welcome led animation
     // After initialization, transition to the menu state
      state = States::MENU;
      break;
    case States::MENU:
      // Display menu options, wait for user input to start the game
      state = States::COMPUTER_TURN;
    break;
    case States::PLAYER_TURN:
      vd.read();
    break;
    case States::COMPUTER_TURN:
        // Computer generates a sequence and displays it
        state = States::PLAYER_TURN;
    case States::END_GAME:
      //Reset game state, display end game message, etc.
    break;
  }
}