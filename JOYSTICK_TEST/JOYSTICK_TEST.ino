 // Define pins for Joystick 1
int joy1PinX = A0;     // Analog pin A0 for Joystick 1 X-axis
int joy1PinY = A1;     // Analog pin A1 for Joystick 1 Y-axis
int joy1ButtonPin = 2; // Digital pin 2 for Joystick 1 button

// Define pins for Joystick 2
int joy2PinX = A2;     // Analog pin A2 for Joystick 2 X-axis
int joy2PinY = A3;     // Analog pin A3 for Joystick 2 Y-axis
int joy2ButtonPin = 3; // Digital pin 3 for Joystick 2 button

// Define pins for LEDs
int ledPinRed1 = 7;    // Connected to digital pin 7 (for Joystick 1 red LED)
int ledPinBlue1 = 8;   // Connected to digital pin 8 (for Joystick 1 blue LED)
int ledPinGreen1 = 9;  // Connected to digital pin 9 (for Joystick 1 green LED)
int ledPinRed2 = 10;   // Connected to digital pin 10 (for Joystick 2 red LED)
int ledPinBlue2 = 11;  // Connected to digital pin 11 (for Joystick 2 blue LED)
int ledPinGreen2 = 12; // Connected to digital pin 12 (for Joystick 2 green LED)

void setup() {
  // Initialize LEDs as outputs
  pinMode(ledPinRed1, OUTPUT);
  pinMode(ledPinBlue1, OUTPUT);
  pinMode(ledPinGreen1, OUTPUT);
  pinMode(ledPinRed2, OUTPUT);
  pinMode(ledPinBlue2, OUTPUT);
  pinMode(ledPinGreen2, OUTPUT);
  
  // Initialize Joystick 1 button pin
  pinMode(joy1ButtonPin, INPUT_PULLUP); // Using internal pull-up resistor
  
  // Initialize Joystick 2 button pin
  pinMode(joy2ButtonPin, INPUT_PULLUP); // Using internal pull-up resistor
  
  // Start serial communication (optional)
  Serial.begin(9600);
}

void loop() {
  // Read Joystick 1 positions
  int joy1xValue = analogRead(joy1PinX);
  int joy1yValue = analogRead(joy1PinY);
  
  // Read Joystick 1 button state (active LOW)
  int joy1ButtonState = digitalRead(joy1ButtonPin);
  
  // Read Joystick 2 positions
  int joy2xValue = analogRead(joy2PinX);
  int joy2yValue = analogRead(joy2PinY);
  
  // Read Joystick 2 button state (active LOW)
  int joy2ButtonState = digitalRead(joy2ButtonPin);
  
  // Joystick 1 LED control
  // Up or down (Y-axis)
  if (joy1yValue < 300) {
    digitalWrite(ledPinBlue1, HIGH);  // Turn on blue LED for Joystick 1
  } else {
    digitalWrite(ledPinBlue1, LOW);   // Turn off blue LED for Joystick 1
  }
  
  // Left or right (X-axis)
  if (joy1xValue < 300) {
    digitalWrite(ledPinRed1, HIGH);   // Turn on red LED for Joystick 1
  } else {
    digitalWrite(ledPinRed1, LOW);    // Turn off red LED for Joystick 1
  }
  
  // Joystick 1 button press
  if (joy1ButtonState == LOW) {
    digitalWrite(ledPinGreen1, HIGH); // Turn on green LED for Joystick 1
  } else {
    digitalWrite(ledPinGreen1, LOW);  // Turn off green LED for Joystick 1
  }
  
  // Joystick 2 LED control
  // Up or down (Y-axis)
  if (joy2yValue < 300) {
    digitalWrite(ledPinBlue2, HIGH);  // Turn on blue LED for Joystick 2
  } else {
    digitalWrite(ledPinBlue2, LOW);   // Turn off blue LED for Joystick 2
  }
  
  // Left or right (X-axis)
  if (joy2xValue < 300) {
    digitalWrite(ledPinRed2, HIGH);   // Turn on red LED for Joystick 2
  } else {
    digitalWrite(ledPinRed2, LOW);    // Turn off red LED for Joystick 2
  }
  
  // Joystick 2 button press
  if (joy2ButtonState == LOW) {
    digitalWrite(ledPinGreen2, HIGH); // Turn on green LED for Joystick 2
  } else {
    digitalWrite(ledPinGreen2, LOW);  // Turn off green LED for Joystick 2
  }
  
  // Print joystick and button states (optional)
  Serial.print("Joystick 1 - X: ");
  Serial.print(joy1xValue);
  Serial.print("\t Y: ");
  Serial.print(joy1yValue);
  Serial.print("\t Button: ");
  Serial.println(joy1ButtonState);
  
  Serial.print("Joystick 2 - X: ");
  Serial.print(joy2xValue);
  Serial.print("\t Y: ");
  Serial.print(joy2yValue);
  Serial.print("\t Button: ");
  Serial.println(joy2ButtonState);
  
  // Add a slight delay to avoid flooding the serial monitor
  delay(100);
}