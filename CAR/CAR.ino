#include <AFMotor.h>

// Define pins for Joystick 1
int joy1pinX = A4;     // Analog pin A0 for Joystick 1 X-axis
int joy1pinY = A5;     // Analog pin A1 for Joystick 1 Y-axis
int joy1ButtonPin = 2; // Digital pin 2 for Joystick 1 button

// Motor Shield setup
AF_DCMotor left2Motor(2);   // Left motor connected to M2
AF_DCMotor right2Motor(1);  // Right motor connected to M1
AF_DCMotor left1Motor(3);
AF_DCMotor right1Motor(4);

const int deadzone = 100; 
int joyLneutral; // X-axis neutral value
int joyRneutral; // Y-axis neutral value

void setup() {
  Serial.begin(9600);       // Start the serial monitor
  left2Motor.setSpeed(255);  // Set motor speed (0 - 255)
  right2Motor.setSpeed(255); // Set motor speed (0 - 255)
  left1Motor.setSpeed(255);
  right1Motor.setSpeed(255);

  // Initialize joystick neutral positions (center values)
  joyLneutral = analogRead(joy1pinX);
  joyRneutral = analogRead(joy1pinY);
}

void loop() {
  // Read joystick positions
  int joypinX = analogRead(joy1pinX);
  int joypinY = analogRead(joy1pinY);
  
  // Forward or backward based on Y-axis
  if ((joypinY - joyRneutral) > deadzone) {
    // Move forward
    left2Motor.run(FORWARD);
    right2Motor.run(FORWARD);
    left1Motor.run(FORWARD);
    right1Motor.run(FORWARD); 
    Serial.print(joypinY);
  }
  else if ((joypinY - joyRneutral) < -deadzone) {
    // Move backward
    left2Motor.run(BACKWARD);
    right2Motor.run(BACKWARD);
    left1Motor.run(BACKWARD);
    right1Motor.run(BACKWARD);  
    Serial.print(joypinY);
  }
  else {
    // Stop motors when within the deadzone
    left2Motor.run(RELEASE);
    right2Motor.run(RELEASE);
    left1Motor.run(RELEASE);
    right1Motor.run(RELEASE);
     Serial.print(joypinX);
  
  }

  // Turn left or right based on X-axis
  if ((joypinX - joyLneutral) > deadzone) {
    // Turn right
    left2Motor.run(FORWARD);
    right2Motor.run(BACKWARD);
    left1Motor.run(FORWARD);
    right1Motor.run(BACKWARD);
    Serial.print(joypinX);  
  
  }
  else if ((joypinX - joyLneutral) < -deadzone) {
    // Turn left
    left2Motor.run(BACKWARD);
    right2Motor.run(FORWARD);
    left1Motor.run(BACKWARD);
    right1Motor.run(FORWARD);  
    
  }
  else {
    // Stop motors if joystick X-axis is in the neutral position
    left2Motor.run(RELEASE);
    right2Motor.run(RELEASE);
    left1Motor.run(RELEASE);
    right1Motor.run(RELEASE);
    
  }
  
}
