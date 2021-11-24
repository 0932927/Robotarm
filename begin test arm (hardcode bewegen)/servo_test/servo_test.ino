#include <VarSpeedServo.h> 
VarSpeedServo servo1;
VarSpeedServo servo2;
VarSpeedServo servo3;

int servoPin1 = 4;
int servoPin2 = 5;
int servoPin3 = 6;

void setup(){
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
}

void loop(){
  servo1.write(100, 20, true);
  delay(1000);
  servo3.write(0, 20, true);
  delay(1000);
  
  servo3.write(120, 20, true);
  delay(1000);
  servo2.write(0, 20, true);
  delay(1000);

  servo3.write(145, 20, false);
//  delay(1000);
  
  servo1.write(115, 20, true);
  delay(2000);
  servo1.write(140, 20, true);
  servo2.write(60, 20, true);
  delay(1000);
  
//  
//  servo1.write(130, 20, true);
//  delay(1000);
//  servo3.write(90, 20, true);
//  delay(1000);
//  servo2.write(80, 20, true);
//  delay(1000);
 
  
}
