#ifndef LED_ANIMATOR_H
#define LED_ANIMATOR_H

#include <Arduino.h>
#include <avr/pgmspace.h>

class LedAnimator {
private:
    bool isLoaded = false;
    bool hasNextFrame = false;
    const uint8_t* frames = nullptr;
    size_t frameCount = 0;
    size_t ledCount = 0;

    const uint8_t* ledPins = nullptr;

    unsigned long interval = 200;
    unsigned long lastUpdate = 0;
    size_t currentFrame = 0;

public:
    LedAnimator() {}

    template <size_t FRAMES, size_t LEDS>
    void load(const uint8_t (&anim)[FRAMES][LEDS],
              const uint8_t (&pins)[LEDS],
              unsigned long frameInterval=200) {

        frames = &anim[0][0];
        frameCount = FRAMES;
        ledCount = LEDS;
        ledPins = pins;
        interval = frameInterval;


        for (size_t i = 0; i < ledCount; i++) {
            pinMode(ledPins[i], OUTPUT);
        }

        isLoaded = true;
        hasNextFrame = true;
    }

    void update() {
        if (millis() - lastUpdate >= interval) {
            lastUpdate = millis();

            for (size_t i = 0; i < ledCount; i++) {
                uint8_t value = pgm_read_byte(
                    frames + (currentFrame * ledCount + i)
                );

                digitalWrite(ledPins[i], value);
            }

            currentFrame++;
            if (currentFrame >= frameCount) {
                hasNextFrame = false;
            }
        }
    }
    
    bool loaded() const {
        return isLoaded;
    } 
    
    bool nextFrame() const {
        return hasNextFrame;
    }
};

#endif