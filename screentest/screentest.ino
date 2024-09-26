void setup() {
  // Start the serial communication
  Serial.begin(9600);  // Make sure the baud rate matches the module's requirements
}

void loop() {
  // Send text to the module
  Serial.println("Hello, World!");
  
  // Wait for a second
  delay(1000);
}