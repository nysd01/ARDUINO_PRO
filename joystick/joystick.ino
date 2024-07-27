int motorPin = 9;
int switch_1 = 4;
int switch_2  = 5;
int switch_3 = 6;
int switch_4 =7;
int btnBreak = 8;
int led = 10;
const int joyLpin = A0;     // left joystick
const int potPin = A2;

int joyL;                   // left joystick reading (0-1023 from ADC)
const int deadzone = 20; 
int joyLneutral;            // left joystick neutral position
int potValue = 0;
int motorSpeed = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(motorPin,OUTPUT);
  pinMode(switch_1,OUTPUT);
  pinMode(switch_2,OUTPUT);
  pinMode(switch_3,OUTPUT);
  pinMode(switch_4,OUTPUT);
  pinMode(led,OUTPUT);
  
   joyLneutral = analogRead(joyLpin);

  
  Serial.begin(9600);
}

void loop() {
  // initialising the potential, switches and joystick values
    potValue = analogRead(potPin);
    joyL = analogRead(joyLpin);
    digitalWrite(motorPin,LOW);
    digitalWrite(switch_1,LOW);
    digitalWrite(switch_3,LOW);
    digitalWrite(switch_4,LOW);
    digitalWrite(switch_2,LOW);
  

  //range of the the potentiometer for speeding
  motorSpeed = map(potValue, 0, 1023, 0, 255);

  // set left motor direction and speed
  if((joyL-joyLneutral) < -deadzone){ // joystick pushed forward
    analogWrite(motorPin, motorSpeed);
    Serial.print(potValue);
    digitalWrite(motorPin,HIGH);
    digitalWrite(led,HIGH);
    digitalWrite(switch_1,HIGH);
    digitalWrite(switch_3,HIGH);
    digitalWrite(switch_4,LOW);
    delay(10);
  }
  
   else if((joyL-joyLneutral) > deadzone){//joystick pushed backward
      analogWrite(motorPin, motorSpeed);
    Serial.print(potValue);
    digitalWrite(motorPin,HIGH);
    digitalWrite(switch_4,HIGH);
    digitalWrite(switch_2,HIGH);
    digitalWrite(switch_1,LOW);
    digitalWrite(switch_4,LOW);
    delay(10);

   }
   else if(btnBreak == HIGH){// button to automatically stop the motor movement
    digitalWrite(motorPin,LOW);
    digitalWrite(switch_4,HIGH);
    digitalWrite(switch_2,HIGH);
    digitalWrite(switch_1,LOW);
    digitalWrite(switch_4,LOW);
    delay(10);
   }
  else{
    digitalWrite(motorPin,LOW);
    digitalWrite(motorPin,LOW);
    digitalWrite(switch_1,LOW);
    digitalWrite(switch_3,LOW);
    digitalWrite(switch_4,LOW);
    digitalWrite(switch_2,LOW);
    digitalWrite(led,LOW);
  }
}

