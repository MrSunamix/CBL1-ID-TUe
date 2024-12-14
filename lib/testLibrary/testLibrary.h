#ifndef TEST_LIBRARY_H
#define TEST_LIBRARY_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>

class DisplayTest {
    public:
        DisplayTest(Adafruit_GC9A01A& display);
        unsigned long testFillScreen();
        unsigned long testText();
        unsigned long testLines(uint16_t color);
        unsigned long testFastLines(uint16_t color1, uint16_t color2);
        unsigned long testRects(uint16_t color);
        unsigned long testFilledRects(uint16_t color1, uint16_t color2);
        unsigned long testFilledCircles(uint8_t radius, uint16_t color);
        unsigned long testCircles(uint8_t radius, uint16_t color);
        unsigned long testTriangles();
        unsigned long testFilledTriangles();
        unsigned long testRoundRects();
        unsigned long testFilledRoundRects();
    private:
        Adafruit_GC9A01A& tft;
};

#endif // TEST_LIBRARY_H