#include <Wire.h>

#define S_NULL 0
#define S_ONTRACE 1

#define m1 3  //Right Motor MA1
#define m2 2  //Right Motor MA2
#define m3 5  //Left Motor MB1
#define m4 4  //Left Motor MB2
#define e1 9  //Right Motor Enable Pin EA
#define e2 10 //Left Motor Enable Pin EB
int InitSpeedL = 50;
int InitSpeedR = 50;

//**********5 Channel IR Sensor Connection**********//
const int ir[5] = {A0, A1, A2, 8, 11};
//*************************************************//

const int trig = 7;     // Set trig pin for HC-SR04
const int echo = 6;     // Set echo pin for HC-SR04

void setup() {
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  pinMode(e1, OUTPUT);
  pinMode(e2, OUTPUT);
  pinMode(trig,OUTPUT);   // Trig pin to emit signal
  pinMode(echo,INPUT);    // Echo pin to receive signal
  
  analogWrite(e1, 0); //you can adjust the speed of the motors from 0-255
  analogWrite(e2, 0); //you can adjust the speed of the motors from 0-255
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
  digitalWrite(m3, HIGH);
  digitalWrite(m4, LOW);

  for(int i = 1; i <= 5; i++)
  pinMode(ir[i], INPUT);

  //Serial.begin(9600);
}

void motorControl(int spdL, int spdR) {
  spdR = -spdR;
  if (spdL < 0) {
    analogWrite(e1, -spdL);
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
  } else {
    analogWrite(e1, spdL);
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
  }

  if (spdR < 0) {
    analogWrite(e2, -spdR);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
  } else {
    analogWrite(e2, spdR);
    digitalWrite(m3, LOW);    
    digitalWrite(m4, HIGH);
  }
}

int bias = 0;
int outlineCnt = 0;

void stateMachine(int a) {
  switch (a) {
    case B00000:
      outlineCnt = 0;
      bias = 0;
      break;
      
    case B11111:
      outlineCnt++;
      break;
      
    case B11101:
    case B11000:
      outlineCnt = 0;
      bias = 2;
      break;
      
    case B11001:
      outlineCnt = 0;
      bias = 1;
      break;
      
    case B11100:
      outlineCnt = 0;
      bias = 3;
      break;

    case B11110:
      outlineCnt = 0;
      bias = 4;
      break;
      
    case B11011:
    case B10001:
      outlineCnt = 0;
      bias = 0;
      break;
      
    case B10011:
      outlineCnt = 0;
      bias = -1;
      break;

    case B10111:
    case B00011:
      outlineCnt = 0;
      bias = -2;
      break;
      
    case B00111:
      outlineCnt = 0;
      bias = -3;
      break;

    case B01111:
      outlineCnt = 0;
      bias = -4;
      break;
      
    default:
      //Serial.println(a, BIN);
      outlineCnt++;
      break;
  }
  
  float ctrl = calcPid(bias);
  motorControl(InitSpeedL - ctrl,InitSpeedR + ctrl);
}

float Kp = 10;
float Ki = 0;
float Kd = 0;
float error, errorLast, erroInte;

float calcPid(float input) {
  float errorDiff;
  float output;
  //error = error * 0.7 + input * 0.3; // filter
  error = input;
  errorDiff = error - errorLast;
  erroInte = constrain(erroInte + error, -50, 50);

  Kp = map(analogRead(A3), 0, 1024, 0, 150);
  Kd = map(analogRead(A5), 0, 1024, 0, 8000);
  
  output = Kp * error + Ki * erroInte + Kd * errorDiff;
//  Serial.print(error); Serial.print(' ');
//  Serial.print(erroInte); Serial.print(' ');
//  Serial.print(errorDiff); Serial.print(' ');
//  Serial.println(output);
  errorLast = error;

  return output;
}

int echoTrace() {
  //Reading Sensor Values
  int Value = 0;
  for(int i = 0; i < 5; i++)
    if(digitalRead(ir[i]) & 1) Value |= (1 << i);

  return Value;
}

int pos;
void loop() {
  InitSpeedL = map(analogRead(A4), 0, 1024, 0, 200);
  InitSpeedR = InitSpeedL + 2;
  pos = echoTrace();
  stateMachine(pos);
}
