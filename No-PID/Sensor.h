#pragma once

#ifndef SENSOR_H
#define SENSOR_H

#include <HCSR04.h>

// Wiring line sensor
int LineSensor[] = {8, 10, 11, 12, 13};
int LineItems = sizeof(LineSensor) / sizeof(LineSensor[0]);

long long P, I, D, PID_value;
int Kp = 0, Ki = 0, Kd = 0, previousError = 0;

//Function
int readError()
{
  int Err = 0;
  for(int i = 0; i < LineItems; i++)
  {
    if(!digitalRead(LineSensor[i]) & 1) // Can change to analogRead to adjust if you make sure that this might helpful.
    {
      Err |= (1 << i);
      Serial.print(1);
    }
    else Serial.print(0);
  }
  Serial.print("    ");
  Serial.println(Err);
  return Err;
}

void PID(int error)
{
  P = error;
  I = I + error;
  D = error - previousError;
  previousError = error;
  
  PID_value = (Kp * P) + (Ki * I) + (Kd * D);
}
#endif
