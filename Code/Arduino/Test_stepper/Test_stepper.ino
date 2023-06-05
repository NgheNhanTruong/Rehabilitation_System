
const int stepPin = 22; 
const int dirPin = 24; 
const int enPin = 4;
void setup() {
  
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);

  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW);
  
}
void loop() {
  
  digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 3200; x++) {
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(80); 
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(80); 
  }
  delay(1000); // One second delay

  digitalWrite(dirPin,LOW); //Changes the rotations direction
  // Makes 400 pulses for making two full cycle rotation
  for(int x = 0; x < 3200; x++) {
    digitalWrite(stepPin,LOW);
    delayMicroseconds(80);
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(80);
  }
  delay(1000);
  
}
