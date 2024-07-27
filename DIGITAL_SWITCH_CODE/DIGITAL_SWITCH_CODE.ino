                                             //REQUIREMENT 
/*
-Transistor
-led
-Diode
-Resistor
-Jumper Wire
-Bread-Board
-Arduino
*/
                                              //setup 
/*
connect the first pin of the transistor to the (Ground)GND.
connect the middle pin of the transistor to one pin of the resistor and the other pin of the resistor to the Arduno digital pin 8
connect the third pin of the transistor to one pin of the diode on that same in connect it to the led negative pin then 
the other to the V5 of the arduino also on that same pin  connect it to the led positive pin

*/
int ledpin = 8;
void setup() {
 pinMode(ledpin,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

 digitalWrite(ledpin,HIGH);
delay(1000);
 digitalWrite(ledpin,LOW);
 delay(1000);
 
}
