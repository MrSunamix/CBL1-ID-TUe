#include <Arduino.h>
#include <FastLED.h>
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_GC9A01A.h"
#include "testLibrary.h"
#include "bootUp.h"
#include "bitmaps.h"

// LED Pin - Using the built-in LED pin from the diagram
#define LED_PIN     48  // GPIO38 is marked as BUILTIN LED on the board
#define NUM_LEDS    1 
#define BRIGHTNESS  50
#define HUE_STEP    1  
#define DELAY_MS    20

// Display pins - Using dedicated SPI pins for ESP32-S3
#define TFT_DC      35
#define TFT_CS      10 
#define TFT_MOSI    11  
#define TFT_SCLK    12  
#define TFT_RST     36

CRGB leds[NUM_LEDS];
uint8_t hue = 0;

// Initialize display with hardware SPI
Adafruit_GC9A01A tft(TFT_CS, TFT_DC, TFT_RST);
DisplayTest displayTest(tft);
bootUp bootScreen(tft, leds, NUM_LEDS);

void setup() {
  printf("GC9A01A Test Starting!\n");

  // Initialize LED strip
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  
  // Set LED to red during initialization
  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();
  
  // Initialize SPI for the display
  SPI.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS);  // SCLK, MISO, MOSI, SS
  delay(100);

  printf("Display initialized successfully!\n");
  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.show();

  // Initialize display tests
  tft.begin();
  tft.setRotation(0);
  tft.fillScreen(GC9A01A_BLACK);
  bootScreen.showBootLogo(5000);

  #if defined(TFT_BL)
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH); // Backlight on
  #endif
  
}

void loop(void) {

}