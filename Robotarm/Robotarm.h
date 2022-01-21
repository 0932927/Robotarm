#ifndef Robotarm_h
#define Robotarm_h
#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)
#include <Arduino.h>
#include <VarSpeedServo.h> 
#include <math.h>
#include <string.h>
#include <stdio.h>


class Robotarm {
    public:
        void attach(); // Dit moet aangeroepen worden in void setup()
		void HerstelServos();
        void DraaiMotor1(uint8_t);
        void DraaiMotor2(int);
        void DraaiMotor3(uint8_t);
		void DraaiMotor4(uint8_t);
        void SluitKop();
        void OpenKop();
		float mirrorM(float);
		void dof2Move(float, float);
		void naarPunt(char, char);
		void circle_method( float, float, float, float);
		void stepperwrite(int a,int b,int c,int d);
		void moveStepper(int angle);
		int hoekverschil(int angle);
		//void Grijpen(); // Uncomment dit wanneer grijper is aangesloten
		float X, Y, Z; // Dit zijn de eind posities
		float Hoek1 =1, Hoek2=2, Hoek3=3;
		float wx, wy, delta, theta_1, theta_2, theta_3, c1, c2, s1, s2;
		float phi;
		float hoek1dof2, hoek2dof2;
		char cijfer;
		char Letter;
		int stepperangleInt = 0;
		int linksRechtsStepper = 2; // 1 is rechtsom 0 is linksom
		int stepperHoek;
		int pin_stepperA = 8;
		int pin_stepperB = 9;
		int pin_stepperC = 10;
		int pin_stepperD = 11;
		double stepperangle = 0;
		int q=0, p=0;
		int stepperKlaar = 0;

    private:
		int pin_Motor1 = 12;// Digitale pin 1 we beginnen bij 2 omdat 0 en 1 ook TX en RX zij voor UART. De servo krijgt telkens een schok voor dat de beweging wordt uitgevoerd
		int pin_Motor2 = 2;//Digitale pin 3
		int pin_Motor3 = 3;//Digitale pin 6
		int pin_Motor4 = 4;//Digitale pin 5
	
		//int pin_Motor5 = 7;//Digitale pin 7 Uncomment dit wanneer grijper is aangesloten
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
		//VarSpeedServo Motor5; // Uncomment dit wanneer grijper is aangesloten
};

#endif
