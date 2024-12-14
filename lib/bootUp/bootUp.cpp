#include "bootUp.h"

bootUp::bootUp(Adafruit_GC9A01A& display, CRGB* ledArray, int numberOfLeds) 
    : tft(display), leds(ledArray), numLeds(numberOfLeds) {
}

void bootUp::showBootLogo(uint16_t displayTime) {
    // Clear screen
    tft.fillScreen(GC9A01A_BLACK);
    
    // Calculate center position for the image (240x240 image)
    int16_t x = (tft.width() - 240) / 2;
    int16_t y = (tft.height() - 240) / 2;
    
    // Draw the bitmap
    tft.drawBitmap(x, y, epd_bitmap_Bitmap, 240, 240, GC9A01A_WHITE);
    
    // Wait specified time
    delay(displayTime);
}

void bootUp::setStatusLED(CRGB color) {
    if (leds && numLeds > 0) {
        fill_solid(leds, numLeds, color);
        FastLED.show();
    }
}

void bootUp::blinkStatusLED(CRGB color, uint16_t blinkRate) {
    if (leds && numLeds > 0) {
        fill_solid(leds, numLeds, color);
        FastLED.show();
        delay(blinkRate);
        fill_solid(leds, numLeds, CRGB::Black);
        FastLED.show();
        delay(blinkRate);
    }
}