int PUL= 6; //define Pulse pin
int DIR= 5; //define Direction pin
int ENA= 4; //define Enable Pin
int PUL2= 9; //define Pulse pin
int DIR2= 8; //define Direction pin
int ENA2= 7; //define Enable Pin
int i = 0;
void setup() {
  pinMode (PUL, OUTPUT);
  pinMode (DIR, OUTPUT);
  pinMode (ENA, OUTPUT);
  digitalWrite(ENA,LOW);
  pinMode (PUL2, OUTPUT);
  pinMode (DIR2, OUTPUT); 
  pinMode (ENA2, OUTPUT);
  digitalWrite(ENA2,LOW);
  digitalWrite(DIR,LOW);
  digitalWrite(DIR2,HIGH);
}

void loop() 
{
  int i = 0;
  for(i ; i <200; i++)
  {
  digitalWrite(PUL,HIGH);
  // digitalWrite(PUL2,HIGH);
  delayMicroseconds(500);
  digitalWrite(PUL,LOW);
  // digitalWrite(PUL2,LOW);
  delayMicroseconds(500);
  }
  delay (2000);
  // for ( int t = 1; t <12800; t++)
  // {
  // digitalWrite(DIR,HIGH);
  // digitalWrite(DIR2,HIGH);
  // digitalWrite(PUL,HIGH);
  // digitalWrite(PUL2,HIGH);
  // delayMicroseconds(40);
  // digitalWrite(PUL,LOW);
  // digitalWrite(PUL2,LOW);
  // delayMicroseconds(40 ); 
  // }
}

