#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define the OLED width and height
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Define the OLED reset pin (for most boards, set to -1 if not needed)
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // Initialize the OLED display with I2C address (0x3C is common)
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Stop if initialization failed
  }

  display.clearDisplay();  // Clear the display buffer
  display.setTextSize(4);  // Set text size to normal
  display.setTextColor(WHITE);  // Set color to white
  display.setCursor(0, 10);  // Set the text cursor
  display.print("NYSD");
  
  display.display();  // Show the message on the screen
}

void loop() {
  // Nothing to do here for now
}
