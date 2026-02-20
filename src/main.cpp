#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include "VoltageDividerInputDetection.h"
#include "enums/game.h"
#include "Led.h"
#include "PushButton.h"
#include "ledAnimations/ledAnimations.h"
#include "ledAnimations/animations.h"

#define LED_COUNT 4
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

Adafruit_SSD1306 display(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, -1); // Initialize display with width, height
const uint8_t ledPins[LED_COUNT] = {4, 5, 6, 7}; // Example LED pins
LedAnimator animator; // Initialize with LED pins

PushButton resetButton(2, "Reset button");

//voltage divider pulldown and load resistors for player input detection
int pullDownResistor = 10000;
int dividerResistors[] = {3000, 6800, 22000};
VoltageDividerInputDetection vd(A0, 10000, dividerResistors, sizeof(dividerResistors) / sizeof(dividerResistors[0]) + 1);

States state;

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
      if(!animator.loaded()) {
        animator.load(welcomeAnimation, ledPins, 150);
      }
      if(animator.nextFrame()) {
        animator.update();
      }
      display.setCursor(0, 15);
      display.println("Simon Says");
      display.display();
     // After initialization, transition to the menu state
      //state = States::MENU;
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