/*
Code to control an ROV with left and right motors
using "tank" steering with two joysticks
*/

// define pins
const int joyLpin = A0;     // left joystick
const int joyRpin = A1;     // right joystick
const int motorLfwd = 7;   // left motor forward pin
const int motorLbck = 8;    // left motor backward pin
const int motorLen = 10;   // left motor enable pin
const int motorRfwd = 9;    // right motor fwd pin
const int motorRbck = 12;    // right motor backward pin
const int motorRen = 11;   // right motor enable pin

// variables
int joyL;                   // left joystick reading (0-1023 from ADC)
int joyR;                   // right joystick reading (0-1023 from ADC)
int joyLneutral;            // left joystick neutral position
int joyRneutral;            // right joystick neutral
const int deadzone = 20;    // joystick "dead zone" to prevent drift
int motorLspeed;            // left motor speed (0-255 for PWM)
int motorRspeed;            // right motor speed (0-255 for PWM)

void setup() { // code that only runs once
  // set motor control pins as outputs
  pinMode(motorLfwd,OUTPUT);
  pinMode(motorRfwd,OUTPUT);
  pinMode(motorLbck,OUTPUT);
  pinMode(motorRbck,OUTPUT);
  pinMode(motorLen,OUTPUT);
  pinMode(motorRen,OUTPUT);
  // calibrate joysticks
  joyLneutral = analogRead(joyLpin);
  joyRneutral = analogRead(joyRpin);

  Serial.begin(9600);

}

void loop() {  // code that loops forever
  // read joysticks
  joyL = analogRead(joyLpin);
  joyR = analogRead(joyRpin);

  Serial.print("Left: ");
  Serial.print(joyL);
  // set left motor direction and speed
  if((joyL-joyLneutral) < -deadzone){ // joystick pushed forward
    digitalWrite(motorLfwd,HIGH);
    digitalWrite(motorLbck,LOW);
    motorLspeed = map(joyL,joyLneutral,0,0,255);
    Serial.print(" fwd ");
  }
  else if((joyL-joyLneutral) > deadzone){
    digitalWrite(motorLfwd,LOW);
    digitalWrite(motorLbck,HIGH);
    motorLspeed = map(joyL,joyLneutral,1023,0,255);
    Serial.print(" back ");
  }
  else{
    digitalWrite(motorLfwd,LOW);
    digitalWrite(motorLbck,LOW);  
    Serial.print(" stop ");    
    motorLspeed = 0; 
  }
  Serial.print(motorLspeed);

  Serial.print(" Right: ");
  Serial.print(joyR);

  // set right motor direction and speed
  if((joyR-joyRneutral) < -deadzone){ // joystick pushed forward
    digitalWrite(motorRfwd,HIGH);
    digitalWrite(motorRbck,LOW);
    motorRspeed = map(joyR,joyRneutral,0,0,255);
    Serial.print(" fwd ");
  }
  else if((joyR-joyRneutral) > deadzone){
    digitalWrite(motorRfwd,LOW);
    digitalWrite(motorRbck,HIGH);
    motorRspeed = map(joyR,joyRneutral,1023,0,255);
    Serial.print(" back ");
  }
  else{
    digitalWrite(motorRfwd,LOW);
    digitalWrite(motorRbck,LOW);  
    Serial.print(" stop ");    
    motorRspeed = 0; 
  }
  Serial.println(motorRspeed);
  analogWrite(motorLen,motorLspeed);
  analogWrite(motorRen,motorRspeed);
  
}
