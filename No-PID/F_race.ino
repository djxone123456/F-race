#define m1 3  //Right Motor MA1
#define m2 2  //Right Motor MA2
#define m3 5  //Left Motor MB1
#define m4 4  //Left Motor MB2
#define e1 9  //Right Motor Enable Pin EA
#define e2 10 //Left Motor Enable Pin EB

//**********5 Channel IR Sensor Connection**********//
const int ir[6] = {0, 11, 8, A2, A1, A0};
//*************************************************//

const int trig = 7;     // chân trig của HC-SR04
const int echo = 6;     // chân echo của HC-SR04

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

unsigned int prev = millis();

void loop() {
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
    
    if(distance <= 15)
    {
      analogWrite(e1, 0); //you can adjust the speed of the motors from 0-255
      analogWrite(e2, 0); //you can adjust the speed of the motors from 0-255
      delay(200);
    }
  }
  
  //Reading Sensor Values
  int s1 = digitalRead(ir[1]);  //Left Most Sensor
  int s2 = digitalRead(ir[2]);  //Left Sensor
  int s3 = digitalRead(ir[3]);  //Middle Sensor
  int s4 = digitalRead(ir[4]);  //Right Sensor
  int s5 = digitalRead(ir[5]);  //Right Most Sensor
  //if only middle sensor detects black line
  if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 1) && (s5 == 1))
  {
    //going forward with full speed 
    analogWrite(e1, 115); //you can adjust the speed of the motors from 0-255
    analogWrite(e2, 115); //you can adjust the speed of the motors from 0-255
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
  }
  
  //if only left sensor detects black line
  if((s1 == 1) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1))
  {
    //going right with full speed 
    analogWrite(e1, 115); //you can adjust the speed of the motors from 0-255
    analogWrite(e2, 115); //you can adjust the speed of the motors from 0-255
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
  }
  
  //if only left most sensor detects black line
  if((s1 == 0) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1))
  {
    //going right with full speed 
    analogWrite(e1, 115); //you can adjust the speed of the motors from 0-255
    analogWrite(e2, 115); //you can adjust the speed of the motors from 0-255
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
  }

  //if only right sensor detects black line
  if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 1))
  {
    //going left with full speed 
    analogWrite(e1, 115); //you can adjust the speed of the motors from 0-255
    analogWrite(e2, 115); //you can adjust the speed of the motors from 0-255
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
  }

  //if only right most sensor detects black line
  if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 0))
  {
    //going left with full speed 
    analogWrite(e1, 115); //you can adjust the speed of the motors from 0-255
    analogWrite(e2, 115); //you can adjust the speed of the motors from 0-255
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
  }

  //if middle and right sensor detects black line
  if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 1))
  {
    //going left with full speed 
    analogWrite(e1, 115); //you can adjust the speed of the motors from 0-255
    analogWrite(e2, 115); //you can adjust the speed of the motors from 0-255
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
  }

  //if middle and left sensor detects black line
  if((s1 == 1) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
  {
    //going right with full speed 
    analogWrite(e1, 115); //you can adjust the speed of the motors from 0-255
    analogWrite(e2, 115); //you can adjust the speed of the motors from 0-255
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
  }

  //if middle, left and left most sensor detects black line
  if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
  {
    //going right with full speed 
    analogWrite(e1, 115); //you can adjust the speed of the motors from 0-255
    analogWrite(e2, 115); //you can adjust the speed of the motors from 0-255
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
  }

  //if middle, right and right most sensor detects black line
  if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 0))
  {
    //going left with full speed 
    analogWrite(e1, 115); //you can adjust the speed of the motors from 0-255
    analogWrite(e2, 115); //you can adjust the speed of the motors from 0-255
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
  }

  //if all sensors are on a black line
  if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0))
  {
      analogWrite(e1, 115); //you can adjust the speed of the motors from 0-255
      analogWrite(e2, 115); //you can adjust the speed of the motors from 0-255
      digitalWrite(m1, HIGH);
      digitalWrite(m2, LOW);
      digitalWrite(m3, HIGH);
      digitalWrite(m4, LOW);
  }
//  int SensorValue = 0;
//  SensorValue = SensorValue * 10 + digitalRead(ir[1]);  //Left Most Sensor
//  SensorValue = SensorValue * 10 + digitalRead(ir[2]);  //Left Sensor
//  SensorValue = SensorValue * 10 + digitalRead(ir[3]);  //Middle Sensor
//  SensorValue = SensorValue * 10 + digitalRead(ir[4]);  //Right Sensor
//  SensorValue = SensorValue * 10 + digitalRead(ir[5]);  //Right Most Sensor
//
//  switch (SensorValue)
//  {
//    case 00000:
//      if (Sonar.dist() < 15)
//      { 
//        delay(90);
//        break;
//      }
//      else Forward();
//      break;
//    
//    case 9001:
//    case 11011:
//      Forward();
//      break;
//
//    case 01111:
//      LeftHalfSpeed();
//      delay(50);
//      break;
//
//    case 11110:
//      RightHalfSpeed();
//      delay(50);
//      break;
//
//    case 1190:
//      RightHalfSpeed();
//      delay(50);
//      break;
//
//    case 00001:
//      RightHalfSpeed();
//      delay(90);
//      break;
//
//    case 9000:
//      LeftHalfSpeed();
//      delay(90);
//      break;
//
//    case 1900:
//      RightHalfSpeed();
//      delay(90);
//      break;
//
//    case 00111:
//      LeftHalfSpeed();
//      delay(50);
//      break;

//    case 00011:
//    case 10111:
//    case 9011:
//      RightHalfSpeed();
//      break;
//
//    case 00111:
//    case 01111:
//    case 00001: // Hơi ngược tí nhưng nó là ngoặc vuông góc
//      RightFullSpeed();
//      break;
//
//    case 1900:
//    case 11101:
//    case 1901:
//      LeftHalfSpeed();
//      break;
//
//    case 1190:
//    case 11110:
//    case 9000: // Hơi ngược tí nhưng nó là ngoặc vuông góc
//      LeftFullSpeed();
//      break;
//
//    default:
//      LeftHalfSpeed();
//      break;
//  }
}

void Forward()
{
  analogWrite(e1, 115); //you can adjust the speed of the motors from 0-255
  analogWrite(e2, 115); //you can adjust the speed of the motors from 0-255
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
  digitalWrite(m3, HIGH);
  digitalWrite(m4, LOW);
}

void LeftHalfSpeed()
{
  analogWrite(e1, 115); //you can adjust the speed of the motors from 0-255
  analogWrite(e2, 25); //you can adjust the speed of the motors from 0-255
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, LOW);
}

void LeftFullSpeed()
{
  analogWrite(e1, 115); //you can adjust the speed of the motors from 0-255
  analogWrite(e2, 115); //you can adjust the speed of the motors from 0-255
  digitalWrite(m1, LOW);
  digitalWrite(m2, HIGH);
  digitalWrite(m3, HIGH);
  digitalWrite(m4, LOW);
}

void RightHalfSpeed()
{
  analogWrite(e1, 25); //you can adjust the speed of the motors from 0-255
  analogWrite(e2, 115); //you can adjust the speed of the motors from 0-255
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(m3, HIGH);
  digitalWrite(m4, LOW);
}

void RightFullSpeed()
{
  analogWrite(e1, 115); //you can adjust the speed of the motors from 0-255
  analogWrite(e2, 115); //you can adjust the speed of the motors from 0-255
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, HIGH);
}
