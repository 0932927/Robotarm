#ifndef Robotarm_h
#define Robotarm_h

#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

#include <Arduino.h>
//#include <Servo.h>
#include <VarSpeedServo.h> 
#include <math.h>
#include <string.h>
#include <stdio.h>




class Robotarm {
    public:
        void attach(); // Dit moet aangeroepen worden in void setup()
		void vastePositie(int);// hier komt het Letter (1 of 2 of 3 ..ect) dan wordt bepaald welke x,y,z
        void GaNaar(uint8_t, uint8_t);// Deze krijgen we van de Arduino sketch, we beginnen eerst met x en y
		void BerekenAantalGraden(float, float);// De gekregen coordinaten in deze functie meegeven om de hoeken te bepalen
        //void DraaiOnderkant(uint8_t);
        void DraaiMotor1(uint8_t);
        void DraaiMotor2(int);
        void DraaiMotor3(uint8_t);
		void DraaiMotor4(uint8_t);
        void SluitKop();
        void OpenKop();
        void AlsGroterDan(uint8_t, uint8_t);
        void AlsKleinerDan(uint8_t, uint8_t);
		void HerstelServos();
		float mirrorM(float);
		void dof2Move(float, float);
		void naarPunt(char, char);
		float X, Y, Z; // Dot zijn de eind posities
		float Hoek1 =1, Hoek2=2, Hoek3=3;
		float wx, wy, delta, theta_1, theta_2, theta_3, c1, c2, s1, s2;
		float phi;
		float hoek1dof2, hoek2dof2;
		char Cijfer;
		char Letter;
    private:
		int pin_Motor1 = 2;// Dig.pin  we beginnen bij 2 omdat 0 en 1 ook TX en RX zij voor UART. De servo krijgt telkens een schok voor dat de beweging wordt uitgevoerd
		int pin_Motor2 = 3;//Dig pin 3
		int pin_Motor3 = 6;//Dig pin 4
		int pin_Motor4 = 5;//Dig pin 5
		float Arm_1 = 12.2; // 5.2; // lengte in cm
		float Arm_2 = 12.5; // 6.9;
		float Arm_3 = 8.0; // 6.8;
		float Arm_2dof2 = Arm_2 + Arm_3;
		float radians;
		float degrees;
		float diff;
		
        VarSpeedServo Motor1;
        VarSpeedServo Motor2;
        VarSpeedServo Motor3;
		VarSpeedServo Motor4;
};

#endif