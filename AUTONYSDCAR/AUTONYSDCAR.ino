#include <AFMotor.h>
#include <Servo.h>

// Motor Shield setup
AF_DCMotor leftMotor(2);   // Left motor connected to M1
AF_DCMotor rightMotor(1);  // Right motor connected to M2

// Servo motor setup
Servo myServo;

// Sonar sensor setup
const int trigPin = 7;
const int echoPin = 6;

// LED pins
const int redLED = 10;

const int blueLED = 12;

void setup() {
  Serial.begin(9600);       // Start the serial monitor
  leftMotor.setSpeed(255);  // Set motor speed (0 - 255)
  rightMotor.setSpeed(255); // Set motor speed (0 - 255)
  
  myServo.attach(9);        // Attach the servo to pin 9
  
  pinMode(trigPin, OUTPUT); // Sonar sensor setup
  pinMode(echoPin, INPUT);
  
  // Set LED pins as output
  pinMode(redLED, OUTPUT);

  pinMode(blueLED, OUTPUT);

  // Turn on the blue LED when system starts (power on)
  digitalWrite(blueLED, HIGH);
}

void loop() {
  long distance = getDistance(); // Get distance from the sonar sensor

  if (distance > 30) {
    // Move forward if the path is clear
    Serial.println("Moving forward");
    leftMotor.run(FORWARD);
    rightMotor.run(FORWARD);
    

    
    // Turn off the red LED
    digitalWrite(redLED, LOW);
  } else {
    // Stop and scan surroundings when an obstacle is detected
    Serial.println("Obstacle detected, scanning...");
    leftMotor.run(RELEASE);
    rightMotor.run(RELEASE);
    
    // Turn on the red LED
    digitalWrite(redLED, HIGH);
    
    // Turn off the white LED

    
    // Scan right
    myServo.write(0);  // Move servo to 0 degrees (right)
    delay(1000);
    long distanceRight = getDistance();

    // Scan left
    myServo.write(180);  // Move servo to 180 degrees (left)
    delay(1000);
    long distanceLeft = getDistance();
    
    // Center the servo
    myServo.write(90);  // Return servo to center (90 degrees)

    // Choose direction based on which side is clearer
    if (distanceRight > distanceLeft) {
      Serial.println("Turning right");
      turnRight();  // Function to turn right
    } else {
      Serial.println("Turning left");
      turnLeft();   // Function to turn left
    }

    // After turning, move straight for 5 seconds
    //delay(5000); // Continue moving straight for 5 seconds
    moveForward(); // Resume moving forward
  }
  
 // delay(100);  // Small delay before the next loop
}

// Function to get distance from sonar sensor
long getDistance() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Convert to distance in cm
  return distance;
}

// Function to move forward
void moveForward() {
  leftMotor.run(FORWARD);
  rightMotor.run(FORWARD);
}

// Function to blink white LED


// Function to turn right (move only left motor forward)
void turnRight() {
  leftMotor.run(FORWARD);
  rightMotor.run(RELEASE);  // Stop right motor to turn right
  delay(8000);  // Adjust delay for a smooth turn
  stopMotors(); // Stop motors after turn
}

// Function to turn left (move only right motor forward)
void turnLeft() {
  leftMotor.run(RELEASE);   // Stop left motor to turn left
  rightMotor.run(FORWARD);
  delay(8000);  // Adjust delay for a smooth turn
  stopMotors(); // Stop motors after turn
}

// Function to stop motors
void stopMotors() {
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
}
