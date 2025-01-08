#include <Arduino.h>
#include <FastLED.h>
#include <Wire.h>
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_GC9A01A.h"
#include "testLibrary.h"
#include "bootUp.h"
#include "bitmaps.h"

// Existing pins definitions remain the same
#define LED_PIN     48
#define NUM_LEDS    1 
#define BRIGHTNESS  50
#define TFT_DC      35
#define TFT_CS      10 
#define TFT_MOSI    11  
#define TFT_SCLK    12  
#define TFT_RST     36

// I2C pins
#define I2C_SDA     8
#define I2C_SCL     9

// TCS3472 Constants
#define TCS3472_ADDR        0x29
#define TCS3472_COMMAND_BIT 0x80
#define TCS3472_ENABLE      0x00
#define TCS3472_ATIME       0x01
#define TCS3472_CONTROL     0x0F
#define TCS3472_CDATAL      0x14    // Clear channel data
#define TCS3472_RDATAL      0x16    // Red channel data
#define TCS3472_GDATAL      0x18    // Green channel data
#define TCS3472_BDATAL      0x1A    // Blue channel data

// Audio definitions
#define SPEAKER_PIN  17

// Musical frequencies
#define NOTE_C5  523
#define NOTE_E5  659
#define NOTE_G5  784
#define NOTE_A5  880

// Global variables (keep your existing ones)
CRGB leds[NUM_LEDS];
Adafruit_GC9A01A tft(TFT_CS, TFT_DC, TFT_RST);
DisplayTest displayTest(tft);
bootUp bootScreen(tft, leds, NUM_LEDS);

struct ColorData {
    uint16_t clear;
    uint16_t red;
    uint16_t green;
    uint16_t blue;
};

// TCS3472 functions
bool initColorSensor() {
    Wire.beginTransmission(TCS3472_ADDR);
    Wire.write(TCS3472_COMMAND_BIT | 0x12); // Read ID register
    Wire.endTransmission();
    
    Wire.requestFrom(TCS3472_ADDR, 1);
    if (Wire.available()) {
        uint8_t id = Wire.read();
        if ((id != 0x44) && (id != 0x4D)) {
            return false;
        }
    } else {
        return false;
    }

    // Enable Power and ADC
    Wire.beginTransmission(TCS3472_ADDR);
    Wire.write(TCS3472_COMMAND_BIT | TCS3472_ENABLE);
    Wire.write(0x03);  // Power ON and ADC enable
    Wire.endTransmission();
    
    // Set integration time (ATIME)
    Wire.beginTransmission(TCS3472_ADDR);
    Wire.write(TCS3472_COMMAND_BIT | TCS3472_ATIME);
    Wire.write(0xF6);  // 24ms integration time
    Wire.endTransmission();
    
    // Set gain (CONTROL)
    Wire.beginTransmission(TCS3472_ADDR);
    Wire.write(TCS3472_COMMAND_BIT | TCS3472_CONTROL);
    Wire.write(0x00);  // 1x gain
    Wire.endTransmission();
    
    delay(50);  // Wait for everything to stabilize
    return true;
}

ColorData readColorData() {
    ColorData data = {0, 0, 0, 0};
    uint8_t bytes[8];
    
    // Read all color data at once
    Wire.beginTransmission(TCS3472_ADDR);
    Wire.write(TCS3472_COMMAND_BIT | TCS3472_CDATAL);
    Wire.endTransmission();
    
    Wire.requestFrom(TCS3472_ADDR, 8);
    for(int i = 0; i < 8 && Wire.available(); i++) {
        bytes[i] = Wire.read();
    }
    
    // Combine bytes into 16-bit values
    data.clear = (bytes[1] << 8) | bytes[0];
    data.red = (bytes[3] << 8) | bytes[2];
    data.green = (bytes[5] << 8) | bytes[4];
    data.blue = (bytes[7] << 8) | bytes[6];
    
    return data;
}


void setup() {
    Serial.begin(115200);
    printf("Starting initialization...\n");
    
    // Initialize I2C
    Wire.begin(I2C_SDA, I2C_SCL);
    
    // Initialize LED strip
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
    
    // Set LED red during init
    fill_solid(leds, NUM_LEDS, CRGB::Red);
    FastLED.show();
    
    // Initialize color sensor
    if (!initColorSensor()) {
        printf("Color sensor initialization failed!\n");
        while(1) {
            delay(100);  // Stay in error state
        }
    }
    printf("Color sensor initialized successfully!\n");
    
    // Your existing display initialization code
    SPI.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS);
    delay(100);
    
    tft.begin();
    tft.setRotation(0);
    tft.fillScreen(GC9A01A_BLACK);
    bootScreen.showBootLogo(5000);
    
    // Set LED green to indicate successful initialization
    fill_solid(leds, NUM_LEDS, CRGB::Green);
    FastLED.show();
}

void loop() {
    ColorData color = readColorData();
    
    // Calculate color ratios
    float total = color.clear;
    float red_ratio = (color.red / total) * 255.0;
    float green_ratio = (color.green / total) * 255.0;
    float blue_ratio = (color.blue / total) * 255.0;
    
    // Update LED color
    leds[0] = CRGB(red_ratio, green_ratio, blue_ratio);
    FastLED.show();
    
    // Update display
    uint16_t displayColor = tft.color565(red_ratio, green_ratio, blue_ratio);
    tft.fillRect(0, 0, 256, 256, displayColor);
    
    // Print debug information
    printf("Color values:\n");
    printf("Clear: %d\n", color.clear);
    printf("Red: %d (ratio: %.2f)\n", color.red, red_ratio);
    printf("Green: %d (ratio: %.2f)\n", color.green, green_ratio);
    printf("Blue: %d (ratio: %.2f)\n", color.blue, blue_ratio);
    printf("\n");
    
    delay(100);  // Adjust delay as needed
}
