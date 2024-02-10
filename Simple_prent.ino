//Setup:
//ESP32 -    Skjár
//GND   -    GND
//V5    -    VCC
//G21   -    SDA
//G22   -    SCL
//
// Skoða hvað allt þetta þýðir
//
// General uppsetningar info;
//
// Til þess að fá tölvuna miðjaða á brauðbrettinu, þá skal hún sett í gat nr. 23.






#include <Wire.h>              // Include the Wire library for I2C communication
#include <Adafruit_GFX.h>      // Include the Adafruit graphics library
#include <Adafruit_SSD1306.h>  // Include the Adafruit SSD1306 OLED display library

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Initialize the SSD1306 display with the I2C address 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // Initialize the display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  // Clear the buffer
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Set text size, in pixels
  display.setTextSize(5);

  // Set cursor position (x, y), in pixels
  display.setCursor(0, 0);

  // Print a letter (e.g., 'A') to the display
  display.print('B');
  display.print('u');
  display.print('i');

  // Display the buffer contents
  display.display();
}

void loop() {
  // Nothing to do here since we're displaying static content in setup()
}
