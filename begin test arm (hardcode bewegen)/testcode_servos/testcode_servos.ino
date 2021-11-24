#include <VarSpeedServo.h> 
VarSpeedServo servo1;
VarSpeedServo servo2;
VarSpeedServo servo3;

int servoPin1 = 0;
int servoPin2 = 1;
int servoPin3 = 2;

void setup(){
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
}

void loop(){
  servo1.write(110, 10, true);
  delay(1000);
  servo2.write(0, 10, true);
  delay(1000);
  servo3.write(110, 10, true);
  delay(1000);
  servo2.write(40, 10, true);
  delay(1000);
  servo1.write(150, 10, true);
  delay(1000);
  servo3.write(140, 10, true);
  delay(1000);
  servo1.write(90, 100, true);
  delay(1000);
}
