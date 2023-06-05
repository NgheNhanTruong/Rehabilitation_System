int ENA_Step_X1=4; //define Enable Pin of Motor Step 1 of X-axis
int DIR_Step_X1=5; //define Direction pin of Step 1 of X-axis

int PUL_Step_X=6; //define Pulse pin of Step common of X-axis

int ENA_Step_X2=7; //define Enable Pin of Motor Step 1 of X-axis
int DIR_Step_X2=8; //define Direction pin of Step 1 of X-axis

int ENA_Step_Y=9; //define Enable Pin of Motor Step 1 of X-axis
int DIR_Step_Y=10; //define Direction pin of Step 1 of X-axis
int PUL_Step_Y=11; //define Pulse pin of Step 1 of X-axis

int temp_X, counter_X = 0; //This variable will increase or decrease depending on the rotation of encoder X-Axis
int temp_Y, counter_Y = 0; //This variable will increase or decrease depending on the rotation of encoder Y-Axis
int temp_step_A, counter_step_A = 0;
int temp_step_B, counter_step_B = 0;

int limitation_X = 6000;
int limitation_Y = 9800;
int limitation_A = 1450;
int limitation_B = 2450;
float Ratio_AX = 0;
float Ratio_BY = 0;

int pulse_X, pulse_Y = 0;

bool start_flag = LOW; // it means not ready for system operation
bool start_flag_X = LOW;
bool start_flag_Y = LOW;
int speed_stepper = 1200;

int XCA[10];


void IXA0() {
  // I0 is activated if DigitalPin nr 2 is going from LOW to HIGH
  // Check pin 3 to determine the direction
  if(digitalRead(3)==LOW) counter_X++;
  else counter_X--;
}
   
void IXA1() {
  // I0 is activated if DigitalPin nr 3 is going from LOW to HIGH
  // Check with pin 2 to determine the direction
  if(digitalRead(2)==LOW) counter_X--;
  else counter_X++;
}

void IYA0() {
  // I0 is activated if DigitalPin nr 20 is going from LOW to HIGH
  // Check pin 3 to determine the direction
  if(digitalRead(20)==LOW) counter_Y++;
  else counter_Y--;
}
   
void IYA1() {
  // ai0 is activated if DigitalPin nr 21 is going from LOW to HIGH
  // Check with pin 2 to determine the direction
  if(digitalRead(21)==LOW) counter_Y--;
  else counter_Y++;
}

//Interrupt function of X-axis occured when the limited switch is active
void ILSXa() {
  if (start_flag_X == LOW) {
    if(digitalRead(19)==LOW) {
      start_flag_X = HIGH;
      Serial.println ("Active Start Flag X");
    }
  }
}

//Interrupt function of Y-axis occured when the limited switch is active
void ILSYa() {
  if ((start_flag_X == HIGH) && (start_flag_Y == LOW)) {
    if(digitalRead(18)==LOW) {
      start_flag_Y = HIGH;
      Serial.println ("Active Start Flag Y");
    }
  }
}

void test_step() {
  digitalWrite(ENA_Step_X1,LOW);
  digitalWrite(DIR_Step_X1,HIGH);
  digitalWrite(PUL_Step_X, HIGH);
  delayMicroseconds(speed_stepper);
  digitalWrite(PUL_Step_X, LOW);
  delayMicroseconds(speed_stepper); 
}

void control_motor_step(bool status,int No_stepper, bool direction,int delay_time) { 
  if (status == HIGH) {
    digitalWrite(ENA_Step_X1,LOW);
    digitalWrite(ENA_Step_X2,LOW);   
    digitalWrite(ENA_Step_Y,LOW);
    if (No_stepper == 1){
      if (direction == HIGH){
      //convention that HIGH is the positive direction
        digitalWrite(DIR_Step_X1,LOW);
        digitalWrite(DIR_Step_X2,HIGH);
      }
      else {
        digitalWrite(DIR_Step_X1,HIGH);
        digitalWrite(DIR_Step_X2,LOW);
      }      
      digitalWrite(PUL_Step_X, HIGH);
      delayMicroseconds(delay_time);
      digitalWrite(PUL_Step_X, LOW);
      delayMicroseconds(delay_time);  
    }
    else if (No_stepper == 2){
      if (direction == HIGH){
        //convention that HIGH is the positive direction
        digitalWrite(DIR_Step_Y,HIGH);
      }
      else {
        digitalWrite(DIR_Step_Y,LOW);
      }
      digitalWrite(PUL_Step_Y,HIGH);
      delayMicroseconds(delay_time);
      digitalWrite(PUL_Step_Y,LOW);
      delayMicroseconds(delay_time);  
    }
  }
  if (status == LOW) {
    if (No_stepper == 1){
      digitalWrite(ENA_Step_X1,HIGH);
      digitalWrite(ENA_Step_X2,HIGH);
    }
    else if (No_stepper == 2){
      digitalWrite(ENA_Step_Y,HIGH);    
    }
    else if (No_stepper == 3){
      digitalWrite(ENA_Step_X1,HIGH);
      digitalWrite(ENA_Step_X2,HIGH);
      digitalWrite(ENA_Step_Y,HIGH);    
    }
  }
}

void update_encoder_counter() {
    // Send the value of counter
  if( counter_X != temp_X ) {
    // Serial.print ("Count Encoder X_axis ");
    // Serial.println (counter_X);
    temp_X = counter_X;
  }
  // Send the value of counter
  if( counter_Y != temp_Y ) {
    // Serial.print("Count Encoder Y_axis ");
    // Serial.println (counter_Y);
    temp_Y = counter_Y;
  }
}

void update_stepper_counter() {
  if( counter_step_A != temp_step_A ) {
    temp_step_A = counter_step_A;
  }
  if( counter_step_B != temp_step_B ) {
    temp_step_B = counter_step_B;
  }
}

void find_limitation_step_motor(){
  update_stepper_counter();
  if (start_flag_X == HIGH) {
    control_motor_step(LOW,1,LOW,0);
    if (start_flag_Y == HIGH) {
      control_motor_step(LOW,2,LOW,0);
      start_flag = HIGH;
      // limitation_X = abs(temp_X); 
      // limitation_Y = abs(temp_Y); 
      // limitation_A = abs(temp_step_A); 
      // limitation_B = abs(temp_step_B); 
      counter_X = 0;
      counter_Y = 0;
      // Serial.print ("Count encoder number limitaton X_axis ");
      // Serial.println (limitation_X);
      // Serial.print ("Count encoder number limitaton Y_axis ");
      // Serial.println (limitation_Y);
      // Serial.print ("Count stepper number limitaton A_axis ");
      // Serial.println (limitation_A);
      // Serial.print ("Count stepper number limitaton B_axis ");
      // Serial.println (limitation_B);
    }
    else {
      control_motor_step(HIGH,2,LOW,speed_stepper);
      counter_step_B ++;
    }
  }
  else {
    control_motor_step(HIGH,1,LOW,speed_stepper);
    counter_step_A ++;
    // control_motor_step_test(HIGH,10);
  }
}

void lineBresenham(int encoderX_current, int encoderY_current, int encoderX_target, int encoderY_target ){
  Ratio_AX = limitation_A / limitation_X;
  
  int x1 = static_cast<float>(encoderX_current) * limitation_A / limitation_X;
  int y1 = static_cast<float>(encoderY_current) * limitation_B / limitation_Y;
  int x2 = static_cast<float>(encoderX_target) * limitation_A / limitation_X;
  int y2 = static_cast<float>(encoderY_target) * limitation_B / limitation_Y;

  int Dx = abs(x2 - x1);
  int Dy = abs(y2 - y1);
  int p = 2*Dy - Dx;
  int c1 = 2*Dy;
  int c2 = 2*(Dy-Dx);
  int x = x1;
  int y = y1;
  int x_unit = 1, y_unit = 1;

  // Consider
  if (x2 - x1 < 0) x_unit = - x_unit;
  if (y2 - y1 < 0) y_unit = - y_unit;
  // trường hợp vẽ đường thẳng đứng
  if (x1 == x2)  { 
    while (y != y2+1){
      delay(10);
      y += y_unit;
      if (y_unit > 0){
        control_motor_step(HIGH,2,HIGH,speed_stepper);
      }
      else {
        control_motor_step(HIGH,2,LOW,speed_stepper);
      }
    }
  }

  else if (y1 == y2)  {  // trường hợp vẽ đường ngang
    while (x != x2+1)
    {
      x += x_unit;
      if (x_unit > 0){
        control_motor_step(HIGH,1,HIGH,speed_stepper);
      }
      else {
        control_motor_step(HIGH,1,LOW,speed_stepper);
      }
    }
  }

  // trường hợp vẽ các đường xiên
  else{          
    // putpixel(x, y, colorRedBlue);
    while(x != x2){
      if (p < 0) p += c1;
      else{
        p += c2;
        y += y_unit;
        if (y_unit > 0){
          control_motor_step(HIGH,2,HIGH,speed_stepper);
        }
        else {
          control_motor_step(HIGH,2,LOW,speed_stepper);
        }
      }
      x += x_unit;
      if (x_unit > 0){
        control_motor_step(HIGH,1,HIGH,speed_stepper);
      }
      else {
        control_motor_step(HIGH,1,LOW,speed_stepper);
      }
    }
  }
}


void Circle_Bresenham(int xc,int yc,int R )	
{	 
  int i = 0 ;
  int p ;
	int y = R ; 
	int x = 0;
	p = 3 - 2*R;
  Serial.print("x bre cir ");
  Serial.print(i);
  Serial.print(" :");
  Serial.print(x);
  Serial.print("-- y bre cir ");
  Serial.print(i);
  Serial.print(" :");
  Serial.println(y);
  int size_array_X = R;
  int XCA[size_array_X];
  XCA[i] = x;
  int size_array_Y = R;
  int YCA[size_array_Y];
  YCA[i] = y;
	while (x < y){
    if (p <0)	p +=4*x+6;
    else {	
      p += 4*(x-y)+10;
      y--;
    }
	  x++;
    i++;
    Serial.print("x bre cir ");
    Serial.print(i);
    Serial.print(" :");
    Serial.print(x);
    Serial.print("-- y bre cir ");
    Serial.print(i);
    Serial.print(" :");
    Serial.println(y);
    XCA[i] = x;
    YCA[i] = y;
	}
  Serial.println(" Array X:");
  for (int j = 0; j < sizeof(XCA) / sizeof(XCA[0]); j++) {
    Serial.println(XCA[j]);
  }
  Serial.println(" Array Y:");
  for (int k = 0; k < sizeof(YCA) / sizeof(YCA[0]); k++) {
    Serial.println(YCA[k]);
  }
}

void setup() {
  Serial.begin(9600);
  //define limit switch signal as input
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(21, INPUT_PULLUP);
  pinMode(20, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);
  //define Stepper1 of X-Axis signals as ouput
  pinMode (ENA_Step_X1, OUTPUT);
  pinMode (DIR_Step_X1, OUTPUT);
  // defing the Pulse pin common for 2 stepper X
  pinMode (PUL_Step_X, OUTPUT); 
  //define Stepper2 of X-Axis signals as ouput
  pinMode (ENA_Step_X2, OUTPUT);
  pinMode (DIR_Step_X2, OUTPUT);
  //define Stepper of Y-Axis signals as ouput
  pinMode (ENA_Step_Y, OUTPUT);
  pinMode (DIR_Step_Y, OUTPUT);
  pinMode (PUL_Step_Y, OUTPUT); 
  digitalWrite(ENA_Step_X1,HIGH);
  digitalWrite(ENA_Step_X2,HIGH);
  digitalWrite(ENA_Step_Y,HIGH);   
  // Define Interrupt pin of Encoder (1) X-Axis
  //A_X rising pulse from encodenren activated ai0(). AttachInterrupt 0 is DigitalPin nr 2 on moust Arduino.
  attachInterrupt(0, IXA0, RISING); 
  //B_X rising pulse from encodenren activated ai1(). AttachInterrupt 1 is DigitalPin nr 3 on moust Arduino.
  attachInterrupt(1, IXA1, RISING);
  // Define Interrupt pin of Encoder (2) Y-Axis
  //A_Y rising pulse from encodenren activated ai0(). AttachInterrupt 2 is DigitalPin nr 21 on moust Arduino.
  attachInterrupt(2, IYA0, RISING);
  //B_Y rising pulse from encodenren activated ai1(). AttachInterrupt 3 is DigitalPin nr 20 on moust Arduino.
  attachInterrupt(3, IYA1, RISING);
  
  // Define Interrupt pin of Limitted_Switches (4) X-Axis
  attachInterrupt(4, ILSXa, FALLING);
  // Define Interrupt pin of Limitted_Switches (4) Y-Axis
  attachInterrupt(5, ILSYa, FALLING);
  delay(20);
  Circle_Bresenham(3,3,8);
  // Serial.println(" Array X:");
  // for (int i = 0; i < sizeof(XCA) / sizeof(XCA[0]); i++) {
  //   Serial.println(XCA[i]);
  // }
}



void loop() {
  // update_encoder_counter (); 
  // // lineBresenham(0,0,1000,1000);   
  // if (start_flag == LOW) {
  //   find_limitation_step_motor();
  // }
  // else {
  //   if((temp_X < 4950 ) && (temp_X < 4950)){
  //     lineBresenham(0,0,5000,5000);    
  //   }
  //   else {
  //     control_motor_step(LOW,3,HIGH,speed_stepper); 
  //   }
  // }  
}




