#pragma once

#ifndef SENSOR_H
#define SENSOR_H

long long PID_value = 0;
int Kp = 0, Ki = 0, Kd = 0, previousError = 0;
int error = 0;
unsigned int prev = millis();

bool NearMe()
{
  if(millis() - prev > 200)
  {
    prev = millis();
    unsigned long duration; // biến đo thời gian
    int distance;           // biến lưu khoảng cách
    
    /* Phát xung từ chân trig */
    digitalWrite(trig,0);   // tắt chân trig
    delayMicroseconds(2);
    digitalWrite(trig,1);   // phát xung từ chân trig
    delayMicroseconds(5);   // xung có độ dài 5 microSeconds
    digitalWrite(trig,0);   // tắt chân trig
    
    /* Tính toán thời gian */
    // Đo độ rộng xung HIGH ở chân echo. 
    duration = pulseIn(echo,HIGH);  
    // Tính khoảng cách đến vật.
    distance = int(duration/2/29.412);
    
    if(distance <= 151)
    {
      analogWrite(e1, 0); //you can adjust the speed of the motors from 0-255
      analogWrite(e2, 0); //you can adjust the speed of the motors from 0-255
      delay(200);
      return 0;
    }
    else return 1;
  }
}

//Function
int readError()
{
  //Reading Sensor Values
  int Value = 0;
  Value = Value * 10 + digitalRead(ir[1]);  //Left Most Sensor
  Value = Value * 10 + digitalRead(ir[2]);  //Left Sensor
  Value = Value * 10 + digitalRead(ir[3]);  //Middle Sensor
  Value = Value * 10 + digitalRead(ir[4]);  //Right Sensor
  Value = Value * 10 + digitalRead(ir[5]);  //Right Most Sensor
  
  switch(Value)
  {
    case 11011: //Mid
      return 0;
      break;

    case 10011: //HR
      return 2;
      break;
      
    case 10111: //HR
    case 00011: //HR
      return 1;
      break;

    case 01111: //R
      return 3;

    case 11110: //L;
      return -3;

    case 11101: //HL
    case 11000:
      return -2;
      
    case 11001:
      return -1;

    case 11111:
      if(error == -3)
        return -4;
      else return 4;
      break;

    case 00000:
      return 0;
      break;
    
    default:
      break;
  }
}

void PID()
{
  P = error;
  I = I + error;
  D = error - previousError;
  previousError = error;
  
  PID_value = (Kp * P) + (Ki * I) + (Kd * D);
}
#endif
