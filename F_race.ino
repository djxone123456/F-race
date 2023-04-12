#define m1 3  //Right Motor MA1
#define m2 2  //Right Motor MA2
#define m3 5  //Left Motor MB1
#define m4 4  //Left Motor MB2
#define e1 9  //Right Motor Enable Pin EA
#define e2 10 //Left Motor Enable Pin EB
#define initial_motor_speed1 100
#define initial_motor_speed2 100

long long P = 25;
long long I = 0;
long long D = 0;

//**********5 Channel IR Sensor Connection**********//
const int ir[6] = {0, A4, A3, A2, A1, A0};
//*************************************************//

const int trig = 7;     // chân trig của HC-SR04
const int echo = 6;     // chân echo của HC-SR04

#include "Sensor.h"

void setup() {
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  pinMode(e1, OUTPUT);
  pinMode(e2, OUTPUT);
  pinMode(trig,OUTPUT);   // chân trig sẽ phát tín hiệu
  pinMode(echo,INPUT);    // chân echo sẽ nhận tín hiệu
  
  analogWrite(e1, 0); //you can adjust the speed of the motors from 0-255
  analogWrite(e2, 0); //you can adjust the speed of the motors from 0-255
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
  digitalWrite(m3, HIGH);
  digitalWrite(m4, LOW);

  for(int i = 1; i <= 5; i++)
  pinMode(ir[i], INPUT);
}

void loop() {
    while(NearMe()) continue;
    
    readError();
    PID();
    int left_motor_speed = initial_motor_speed1 - PID_value;
    int right_motor_speed = initial_motor_speed2 + PID_value;
    
    // The motor speed should not exceed the max PWM value
    constrain(left_motor_speed,0,255);
    constrain(right_motor_speed,0,255);

    analogWrite(e1, left_motor_speed); //you can adjust the speed of the motors from 0-255
    analogWrite(e2, right_motor_speed); //you can adjust the speed of the motors from 0-255

    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
  }
