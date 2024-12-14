#ifndef BOOT_UP_H
#define BOOT_UP_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>
#include <FastLED.h>

// Bitmap data declarations
extern const unsigned char epd_bitmap_Bitmap[];

// Note: The GFXbitmapGlyph and GFXbitmapFont need their structures defined
struct GFXbitmapGlyph {
    uint32_t bitmapOffset;     // Pointer into bitmap
    uint8_t width, height;     // Bitmap dimensions in pixels
    uint8_t xAdvance;         // Distance to advance cursor
    int8_t xOffset, yOffset;  // Dist from cursor position to UL corner
    uint8_t glyph;           // ASCII character represented
};

struct GFXbitmapFont {
    const uint8_t* bitmap;      // Bitmap data
    const GFXbitmapGlyph* glyph; // Glyph array
    uint8_t first, last;        // ASCII range
};

extern const GFXbitmapGlyph epd_bitmap_Glyphs[];
extern const GFXbitmapFont epd_bitmap_Font;

class bootUp {
    public:
        bootUp(Adafruit_GC9A01A& display, CRGB* leds, int numLeds);
        void showBootLogo(uint16_t displayTime = 2000);
        void setStatusLED(CRGB color);
        void blinkStatusLED(CRGB color, uint16_t blinkRate = 200);
        
    private:
        Adafruit_GC9A01A& tft;
        CRGB* leds;
        int numLeds;
};

#endif // BOOT_UP_H