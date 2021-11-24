#include "Robotarm.h"



void Robotarm::attach() {
    Motor1.attach(pin_Motor1);// base motor
    Motor2.attach(pin_Motor2);// op de base arm 1
    Motor3.attach(pin_Motor3);// arm2
	Motor4.attach(pin_Motor4);// op servo
}

void Robotarm::HerstelServos()// om de arm naar de standaard posities terug te zetten
{
	Motor1.write(90, 30, true);// misschien is het niet nodig voor motor 1 omdat deze de base motor is
	delay(1000);
	Motor2.write(10, 30, true);
	delay(500);
	Motor3.write(45, 40, true);
	delay(500);
	Motor4.write(45, 40, true);
	delay(500);
}

//float X2 = 10.0;
//float Y2 = 10.0;
void Robotarm::BerekenAantalGraden(float X2,float Y2)
{
	phi = 180.0;
	degToRad(phi); // zelf gedefinieerd in robotarm.h
	int wx = X2 - Arm_3*cos(phi);
	int wy = Y2 - Arm_3*sin(phi);
	
	float delta = (wx*wx)+ (wy*wy);
	float c2 = (delta - (Arm_1*Arm_1) - (Arm_2*Arm_2))/(2 * Arm_1 * Arm_2);
	float s2 = sqrt(1 - (c2*c2));
	float theta_2 = atan2(s2, c2);
	float s1 = ((Arm_1+Arm_2*c2)*wy - Arm_2*s2*wx)/delta;
	float c1 = ((Arm_1+Arm_2*c2)*wx + Arm_2*s2*wy)/delta;
	float theta_1 = atan2(s1,c1);
	float theta_3 = phi-theta_1-theta_2;
	float Hoek1 = theta_1;
	float Hoek2 = theta_2;
	float Hoek3 = theta_3;
}

void Robotarm::CoordinatenBepalen(int Getal)
{
	if (Getal == 1)
	{
		Motor3.write(-45, 30, true);
		return;
		//BerekenAantalGraden(float, float) // hier worden de x en y meegegeven afhankelijjk van welke getal is gekozen
	}
	else if(Getal == 2)
	{
		Motor3.write(45, 30, true);
		return;
		//BerekenAantalGraden(float, float)
	}
	else if(Getal == 3)
	{
		Motor3.write(70, 30, true);
		return;
		//BerekenAantalGraden(float, float)
	}
	else if(Getal == 4)
	{
		Motor3.write(-100, 30, true);
		return;
		//BerekenAantalGraden(float, float)
	}
}	
void Robotarm::GaNaar(uint8_t x, uint8_t y) //coordinaten moeten hier doorgegeven worden, eerst alleen x en y
{
	//Motor1.write();
	//delay(500);
	//Motor2.write();
	//delay(500);
	//Motor3.write();
	//delay(500);
	//Motor4.write();
	//(500);
}

//void Robotarm::DraaiOnderkant(uint8_t aantalgraden) Deze functie is hetzelfde als draarmotor 1 want motor1 wordt in de base geplaatst
//{

//}

void Robotarm::DraaiMotor1(uint8_t aantalgraden) 
{
    Motor1.write(aantalgraden, 30, true);
	return;
}

void Robotarm::DraaiMotor2(int aantalgraden) 
{
    Motor2.write(aantalgraden, 30, true);
}

void Robotarm::DraaiMotor3(uint8_t aantalgraden) 
{
    Motor3.write(aantalgraden, 30, true);
}

void Robotarm::DraaiMotor4(uint8_t aantalgraden) 
{
    Motor4.write(aantalgraden, 30, true);
}

void Robotarm::SluitKop() {
	//DraaiMotor5 wanneer deze wordt aangesloten voor de kop
}

void Robotarm::OpenKop() {
	//DraaiMotor5 wanneer deze wordt aangesloten voor de kop
}

void Robotarm::AlsGroterDan(uint8_t a, uint8_t b) 
{

}

void Robotarm::AlsKleinerDan(uint8_t a, uint8_t b) 
{

}
