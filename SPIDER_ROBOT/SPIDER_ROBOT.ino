#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Create the PWM driver instance
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Define the minimum and maximum pulse lengths (for servos)
#define SERVOMIN 150  // Minimum pulse length count (0 degrees)
#define SERVOMAX 600  // Maximum pulse length count (180 degrees)

// Convert angle to pulse length
int angleToPulse(int angle) {
  return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  // Initialize the PWM driver
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz frequency
  delay(10);
}

void setServoAngle(int servoNum, int angle) {
  int pulse = angleToPulse(angle);
  pwm.setPWM(servoNum, 0, pulse);

setServoAngle(0, 90);  // FRONT RIGHT LEG UPPERJOINT
  setServoAngle(1, 180); // FRONT RIGHT LEG KNEE JOINT
  setServoAngle(2, 90);  // FRONT LEFT LEG UPPERJOINT
  setServoAngle(3, 180);  // FRONT LEFT LEG KNEE JOINT
  setServoAngle(4, 90);  // BACK RIGHT LEG UPPERJOINT
  setServoAngle(5, 180);  // BACK RIGHT LEG KNEE JOINT
  setServoAngle(6, 90);  // BACK LEFT LEG UPPERJOINT
  setServoAngle(7, 180); // BACK LEFT LEG KNEE JOINT
}


void loop() {

  
}
