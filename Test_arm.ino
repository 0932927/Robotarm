#include "VarSpeedServo.h"
/* Servo control for AL5D arm */
/* Arm dimensions( mm ) */
#define BASE_HGT 51 //base height
#define HUMERUS 122 //shoulder-to-elbow "bone"
#define ULNA 125 //elbow-to-wrist "bone"
#define GRIPPER 50 //gripper (incl.heavy duty wrist rotate mechanism) length "

#define ftl(x) ((x)>=0?(long)((x)+0.5):(long)((x)-0.5)) //float to long conversion

/* Servo names/numbers *
  Base servo HS-485HB */
#define BAS_SERVO 2
/* Shoulder Servo HS-5745-MG */
#define SHL_SERVO 3
/* Elbow Servo HS-5745-MG */
#define ELB_SERVO 6
/* Wrist servo HS-645MG */
#define WRI_SERVO 5

#define epsilon 0.00001

/* pre-calculations */
float hum_sq = HUMERUS * HUMERUS;
float uln_sq = ULNA * ULNA;

int servoSpeed = 10;

//ServoShield servos; //ServoShield object
VarSpeedServo servo1, servo2, servo3, servo4;

int loopCounter = 0;
int pulseWidth = 6.6;
int microsecondsToDegrees;

void setup()
{
  servo1.attach( BAS_SERVO );
  servo2.attach( SHL_SERVO );
  servo3.attach( ELB_SERVO );
  servo4.attach( WRI_SERVO );
  //  servo5.attach( WRO_SERVO, 544, 2400 );
  //  servo6.attach( GRI_SERVO, 544, 2400 );
  delay(1000);
  servo_park();
  delay(4000);
  Serial.begin( 9600 );
  Serial.println("Start");
}

void loop() {
  loopCounter += 1;
  circle_method(0, 200, 100, 0, 10);
  delay(10000);
  circle_method(-200, 100, 100, 0, 10);
  delay(10000);
  circle_method(0, 100, 200, 0, 10);
  delay(10000);
  if (loopCounter > 1) {
    servo_park();
    delay(5000);
    Serial.println("Done");
    exit(0);
  }//pause program - hit reset to continue
  //exit(0);
}

/* arm positioning routine utilizing inverse kinematics */
/* z is height, y is distance from base center out, x is side to side. y,z can only be positive */
//void set_arm( uint16_t x, uint16_t y, uint16_t z, uint16_t grip_angle )

void circle_method( float x, float y, float z, float grip_angle_d, int servoSpeed) {
  x == 0 ? epsilon : x;
  y == 0 ? epsilon : y;
  z == 0 ? epsilon : z;
  float base_angle_r = atan2(x, y);
  float base_angle_d = degrees(base_angle_r);

  //calculate arm points
  float grip_offset_z = sin(grip_angle_d) * GRIPPER;
  float grip_offset_y = cos(grip_angle_d) * GRIPPER;
  
  float wrist_y = y - grip_offset_y;
  float wrist_z = z - grip_offset_z;
  
  
  float shoulder_y = 0;
  float shoulder_z = 0;
  
  float dy = abs(wrist_y - shoulder_y);
  float dz = abs(wrist_z - shoulder_z);
  float dist = sqrt(sq(dy) + sq(dz));

  if (dist > ULNA + HUMERUS) {
    Serial.println("Error: Out of range!");
    return;
  } else if (dist < abs(ULNA - HUMERUS)) {
    Serial.println("Error: Too close!");
    return;
  } else if ((dist == 0) and (ULNA == HUMERUS)) {
    Serial.println("Error: Exactly the same so idk how u got this");
    return;
  }
  
  float elbow_z;
  float elbow_y;

  //some intersection magic
  float a = (abs(hum_sq - uln_sq) + sq(dist)) / (2*dist);
  float h = sqrt(hum_sq - sq(a));

  float ym = shoulder_y + a*dy/dist;
  float zm = shoulder_z + a*dz/dist;

  float ys1 = ym + h*dz/dist;
  float zs1 = zm - h*dy/dist;
  
  float ys2 = ym - h*dz/dist;
  float zs2 = zm + h*dy/dist;

  Serial.print("Wrist Point : (");
  Serial.print(wrist_y);
  Serial.print(",");
  Serial.print(wrist_z);
  Serial.println(")");
  
  //whichever intersection is more up
  if (zs1 > zs2) {
    elbow_z = zs1;
    elbow_y = ys1;
  } else {
    elbow_z = zs2;
    elbow_y = ys2;
  }
  Serial.print("Elbow Point : (");
  Serial.print(elbow_y);
  Serial.print(",");
  Serial.print(elbow_z);
  Serial.println(")");
  
  float shoulder_angle_d = degrees( atan2( abs(elbow_z - shoulder_z), abs(elbow_y - shoulder_y) ) );
  float elbow_angle_d =  -(degrees( atan2( abs(wrist_z - elbow_z), abs(wrist_y - elbow_y) ) ) - shoulder_angle_d );
  float wrist_angle_d = degrees( atan2(z - wrist_z, y - wrist_y)) - elbow_angle_d - shoulder_angle_d + 180;
  
  Serial.print("Angles : ");
  Serial.print(base_angle_d);
  Serial.print(" ");
  Serial.print(shoulder_angle_d);
  Serial.print(" ");
  Serial.print(elbow_angle_d);
  Serial.print(" ");
  Serial.println(wrist_angle_d);
  
  servo1.write(base_angle_d + 180, servoSpeed); //anti negatives direction fix
  servo2.write(shoulder_angle_d, servoSpeed);
  servo3.write(180 - elbow_angle_d, servoSpeed); //diretion fix
  servo4.write(180 - wrist_angle_d, servoSpeed); //direction fix
  return;
}

void servo_park() {
  servo1.write(0, 30, true);
  servo2.write(135, 30, true);
  servo3.write(180, 30, true);
  servo4.write(135, 30, true);
  return;
}
