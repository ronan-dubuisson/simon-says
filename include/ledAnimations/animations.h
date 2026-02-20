#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <Arduino.h>
#include <avr/pgmspace.h>

#define LED_COUNT 4

// Animation frames: frames × LEDs
const uint8_t welcomeAnimation[][LED_COUNT] PROGMEM = {
  {1, 0, 0, 0},
  {0, 1, 0, 0},
  {0, 0, 1, 0},
  {0, 0, 0, 1},
  {0, 0, 1, 0},
  {0, 1, 0, 0},
  {1, 0, 0, 0},
  {1, 1, 1, 1},
  {0, 0, 0, 0},
  {1, 1, 1, 1},
  {0, 0, 0, 0},
  {1, 1, 1, 1},
  {0, 0, 0, 0},
  {1, 1, 1, 1},
  {0, 0, 0, 0},
};

#endif