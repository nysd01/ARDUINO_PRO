#include "DFRobotDFPlayerMini.h"
#include <SoftwareSerial.h>

SoftwareSerial mySoftwareSerial(10,11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

// Piano buttons (8 buttons for different notes)
const int pianoButtons[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int numButtons = 8;  // Total number of piano buttons
// Music button (play or skip tracks)
const int musicButton = 0;

const int ledPianoOn = 1;   // LED that stays on when piano is active
const int ledBlink = 12;     // LED that blinks with a delay
const int ledPiano = 13;     // LED for piano activity

// Timing for blinking LED
unsigned long lastBlinkTime = 0;
const unsigned long blinkInterval = 500;  // Blinking interval (0.5 second)

// Timing for double press detection
unsigned long lastPressTime = 0;
const unsigned long doublePressInterval = 400;  // Max interval between double presses (ms)
int currentTrack = 1;
bool playSingleTrack = false;

const int potPin = A0;

// Flag to prevent welcome message from playing multiple times
bool welcomePlayed = false;
void setup()
{
  pinMode(ledPianoOn, OUTPUT);
  pinMode(ledBlink, OUTPUT);
  pinMode(ledPiano, OUTPUT);


  mySoftwareSerial.begin(9600);
  myDFPlayer.begin(mySoftwareSerial);
  myDFPlayer.volume(1);  // Set volume level
  // Loop background music on startup

  digitalWrite(ledPianoOn, HIGH);
  digitalWrite(ledPiano, HIGH);

    // Setup input for piano buttons
  for (int i = 0; i < numButtons; i++) {
    pinMode(pianoButtons[i], INPUT_PULLUP);
  }
  pinMode(musicButton, INPUT_PULLUP);  // Setup music button

  // Play welcome message if it hasn’t been played yet
  if (!welcomePlayed) {
    myDFPlayer.playFolder(1,1);  // Play "Welcome, NYSD, the boss" from FOLDER 01
    Serial.println("Playing welcome message");
    welcomePlayed = true;  // Ensure welcome message plays only once
    delay(3000);  // Delay to allow the message to finish playing
  }



}

void loop()
{
  while(true){
  // put your main code here, to run repeatedly:
   int volumeValue = analogRead(potPin);
  int volume = map(volumeValue, 0, 1023, 0, 30);  // Map potentiometer value to volume (0 to 30)
  myDFPlayer.volume(volume);

  // Blink the LED on pin 12 at a 0.5-second interval
  unsigned long currentTime = millis();
  if (currentTime - lastBlinkTime >= blinkInterval) {
    // Toggle the blinking LED
    digitalWrite(ledBlink, !digitalRead(ledBlink));
    lastBlinkTime = currentTime;
  }
  // Check each piano button and play corresponding sound
  for (int i = 0; i < numButtons; i++) {
    if (digitalRead(pianoButtons[i]) == LOW) {
      myDFPlayer.playFolder(2, i + 1);  // Play corresponding sound from FOLDER 02
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
      myDFPlayer.playFolder(2, currentTrack);  // Play next track from FOLDER 02
      Serial.println("Track changed");
    } else {
      // Single press detected, play current track
      if (!playSingleTrack) {
        myDFPlayer.playFolder(2, currentTrack);  // Play track from FOLDER 02
        playSingleTrack = true;
        Serial.println("Playing specific song");
      }
    }

    lastPressTime = currentPressTime;
    delay(300);  // Debounce to avoid multiple presses
  }
  }
}
