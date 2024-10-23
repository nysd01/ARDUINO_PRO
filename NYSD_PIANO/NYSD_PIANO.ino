#include <DFPlayerMini_Fast.h>   // Ensure this library is installed
#include <SoftwareSerial.h>

// Software Serial for DFPlayer Mini
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX for DFPlayer Mini
DFPlayerMini_Fast mp3;  // Use the correct class for the DFPlayer

// Piano buttons (8 buttons for different notes)
const int pianoButtons[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int numButtons = 8;  // Total number of piano buttons

// Music button (play or skip tracks)
const int musicButton = 10;

// Potentiometer for volume control
const int potPin = A0;

// LEDs
const int ledPianoOn = 13;   // LED that stays on when piano is active
const int ledBlink = 12;     // LED that blinks with a delay
const int ledPiano = 11;     // LED for piano activity

// Timing for double press detection
unsigned long lastPressTime = 0;
const unsigned long doublePressInterval = 400;  // Max interval between double presses (ms)
int currentTrack = 1;
bool playSingleTrack = false;

// Timing for blinking LED
unsigned long lastBlinkTime = 0;
const unsigned long blinkInterval = 500;  // Blinking interval (0.5 second)

// Flag to prevent welcome message from playing multiple times
bool welcomePlayed = false;

void setup() {
  // Initialize serial communication for DFPlayer Mini
  mySoftwareSerial.begin(9600);
  delay(300);  // Wait for serial connection to stabilize

  // Initialize DFPlayer Mini
  if (!mp3.begin(mySoftwareSerial)) {
    Serial.println("Error initializing MP3 module");
    while (true);  // Stop execution if MP3 initialization fails
  }
Serial.println("DFPlayer Mini initialisé avec succès");
  mp3.volume(10);
  // Setup input for piano buttons
  for (int i = 0; i < numButtons; i++) {
    pinMode(pianoButtons[i], INPUT_PULLUP);
  }
  pinMode(musicButton, INPUT_PULLUP);  // Setup music button

  // Setup output for LEDs
  pinMode(ledPianoOn, OUTPUT);
  pinMode(ledBlink, OUTPUT);
  pinMode(ledPiano, OUTPUT);

  // Turn on piano LEDs
  digitalWrite(ledPianoOn, HIGH);
  digitalWrite(ledPiano, HIGH);

  // Play welcome message if it hasn’t been played yet
  if (!welcomePlayed) {
    mp3.playFolder(1, 1);  // Play "Welcome, NYSD, the boss" from FOLDER 01
    Serial.println("Playing welcome message");
    welcomePlayed = true;  // Ensure welcome message plays only once
    delay(3000);  // Delay to allow the message to finish playing
  }

  // Print ready message
  Serial.println("MP3 player ready!");
}

void loop() {
  digitalWrite(ledPianoOn, HIGH);  // Keep the piano LED on

  // Blink the LED on pin 12 at a 0.5-second interval
  unsigned long currentTime = millis();
  if (currentTime - lastBlinkTime >= blinkInterval) {
    // Toggle the blinking LED
    digitalWrite(ledBlink, !digitalRead(ledBlink));
    lastBlinkTime = currentTime;
  }

  // Read potentiometer value and adjust volume
  int volumeValue = analogRead(potPin);
  int volume = map(volumeValue, 0, 1023, 0, 30);  // Map potentiometer value to volume (0 to 30)
  mp3.volume(7);

  // Check each piano button and play corresponding sound
  for (int i = 0; i < numButtons; i++) {
    if (digitalRead(pianoButtons[i]) == LOW) {
      mp3.playFolder(1, i + 1);  // Play corresponding sound from FOLDER 01
      delay(300);  // Short delay to prevent multiple triggers
    }
  }

  // Check the music button for single or double press
  if (digitalRead(musicButton) == LOW) {
    unsigned long currentPressTime = millis();

    if (currentPressTime - lastPressTime < doublePressInterval) {
      // Double press detected, change track
      currentTrack++;
      if (currentTrack > 3) currentTrack = 1;  // Loop through 3 tracks in FOLDER 02
      mp3.playFolder(2, currentTrack);  // Play next track from FOLDER 02
      Serial.println("Track changed");
    } else {
      // Single press detected, play current track
      if (!playSingleTrack) {
        mp3.playFolder(2, currentTrack);  // Play track from FOLDER 02
        playSingleTrack = true;
        Serial.println("Playing specific song");
      }
    }

    lastPressTime = currentPressTime;
    delay(300);  // Debounce to avoid multiple presses
  }
}
