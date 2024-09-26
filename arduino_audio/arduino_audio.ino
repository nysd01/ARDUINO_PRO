const int playPin = 2; // Pin to send play signal to the MP3 module
const int buttonPin = 5; // Pin connected to the button

void setup() {
  pinMode(playPin, OUTPUT);
  digitalWrite(playPin, LOW); // Ensure playPin is LOW
  
  pinMode(buttonPin, INPUT_PULLUP); // Set button pin as input with internal pull-up resistor
  
  Serial.begin(9600); // Initialize serial communication for debugging
  delay(1000); // Wait for the module to initialize
}

void loop() {
  // Check if the button is pressed
  if (digitalRead(buttonPin) == LOW) {
    Serial.println("Button Pressed - Playing MP3");
    play();
    delay(1000); // Debounce delay to avoid multiple triggers
  }
}

void play() {
  digitalWrite(playPin, HIGH); // Simulate button press
  delay(500); // Delay for button press duration
  digitalWrite(playPin, LOW); // Release button
}
