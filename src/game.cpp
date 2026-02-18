#include "game.h"
#include "Led.h"

int dividerResistors[] = {3000, 6800, 22000};

Game::Game(byte ledPins[], byte playerInputPin) :
  _leds{Led(ledPins[0], "RED"), Led(ledPins[1], "GREEN"), Led(ledPins[2], "YELLOW"), Led(ledPins[3],"BLUE")},
  _playerInput(playerInputPin, 10000, dividerResistors, sizeof(dividerResistors) / sizeof(dividerResistors[0]) + 1)
{
}

/**
 * private method to blink all leds a certain amount of times for a visual effect at start or reset of the game
 */
void Game::_blinkLeds() {
  for (int count = 0; count < 5; count++) {
    for (Led led : _leds) {
      led.update(HIGH);
      delay(_blinkInterval);
      led.update(LOW);
    } 
  }

  delay (_blinkInterval + 200);

  for (int count = 0; count < 3; count++) {
    for (Led led : _leds) {
      led.update(HIGH);
    } 
    delay(_blinkInterval + 200);
    for (Led led : _leds) {
      led.update(LOW);
    } 
    delay(_blinkInterval+ 200);
  }
}

/**
  * public method to toggle a single led for a set time
  */
void Game::_toggleSingleLed(byte ledPin) {
  digitalWrite(ledPin, HIGH);
  delay(_sequenceDuration);
  digitalWrite(ledPin, LOW);
}

/**
 * public method to power off all leds in case of reset or end of game
 */
void Game::_powerOffAllLeds() {
  for (Led led : _leds) {
    led.update(LOW);
  }
}

/**
 * public method to start a new game
 */
void Game::startNewGame() {
  _blinkLeds();
  delay(_waitStartInterval);
}

/**
 * public method to reset the game
 */
void Game::resetGame() {
  _sequenceArray = SequenceArray(); // Reset the sequence array
  _powerOffAllLeds();
  isReset = false;
}

/**
 * public method to start a new color sequence
 */
void Game::newColorSequence() {
   _sequenceArray.addToSequence();

   for(Led led : _leds){
    if(led.getLabel()==_sequenceArray.getLastElement()){
      led.update(HIGH);
      delay(_sequenceDuration);
      led.update(LOW);
    }
   }
}

/**
 * Verify sequence
 */
bool Game::verifySequence(String pressedButton){
  if(_sequenceArray.getLastElement() == pressedButton){
    return true;
  } else {
    return false;
  }
}