#include <AFMotor.h>

// Motor Shield setup
AF_DCMotor leftMotor(2);   // Left motor connected to M1
AF_DCMotor rightMotor(1);  // Right motor connected to M2
AF_DCMotor powerForwardMotor(3);



void setup() {
  Serial.begin(9600);       // Start the serial monitor
  leftMotor.setSpeed(255);  // Set motor speed (0 - 255)
  rightMotor.setSpeed(255); // Set motor speed (0 - 255)
  powerForwardMotor.setSpeed(255);
 
}

void loop() {

    leftMotor.run(FORWARD);
    rightMotor.run(FORWARD);
    
    powerForwardMotor.run(FORWARD);
    
}