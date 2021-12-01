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
	Motor2.write(90, 30, true);
	delay(500);
	Motor3.write(90, 40, true);
	delay(500);
	Motor4.write(90, 40, true);
	delay(500);
}

void Robotarm::BerekenAantalGraden(float X,float Y)
{
	phi = 180.0;
	phi = degToRad(phi); // zelf gedefinieerd in robotarm.h

	wx = X - Arm_3*cos(phi);
	wy = Y - Arm_3*sin(phi);

	delta = pow(wx, 2)+ pow(wy, 2);
	c2 = (delta - pow(Arm_1, 2) - pow(Arm_2, 2))/(2 * Arm_1 * Arm_2);
	s2 = sqrt(1 - pow(c2,2));
	theta_2 = atan2(s2, c2);

	s1 = ((Arm_1+Arm_2*c2)*wy - Arm_2*s2*wx)/delta;
	c1 = ((Arm_1+Arm_2*c2)*wx + Arm_2*s2*wy)/delta;
	theta_1 = atan2(s1,c1);
	theta_3 = phi-theta_1-theta_2;

	Hoek1 = radToDeg(theta_1)+90;
	Hoek2 = radToDeg(theta_2);
	Hoek3 = radToDeg(theta_3);
}

//
void Robotarm::vastePositie(int Getal)
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
	aantalgraden = mirrorM(aantalgraden);
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

float Robotarm::mirrorM(float hoek){
	//als de hoek kleiner is dan 90 moet de mirror groter zijn dan 90
	//de mirror van 89 is 91. 
	//wanneer de hoek dus kleiner is moet het verschil tot 90 bij 90 worden opgeteld
	if (hoek < 90.0) 
	{ 
		diff = 90.0 - hoek;
		hoek = 90.0 + diff;
	} else {
		diff = hoek - 90.0;
		hoek = 90.0 - diff;
	}
	return hoek;
	
}

void Robotarm::RoteerNaar(float X, float Z) //coordinaten moeten hier doorgegeven worden, eerst alleen x en y
{
	double angle = atan2(Z, X) * 180 / M_PI; // Slope Z, Slope X
    if(angle<0){
      angle= 360+angle;
    }
    else if(angle>0){
		angle = angle;
    }
	Motor1.write(angle);
}
