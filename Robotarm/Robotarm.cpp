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
	phi = 0.0;
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

	Hoek1 = radToDeg(theta_1);
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

void Robotarm::DraaiMotor1(uint8_t aantalgraden) {
    Motor1.write(aantalgraden, 30, true);
	return;
}

void Robotarm::DraaiMotor2(int aantalgraden) {		
	aantalgraden = mirrorM(aantalgraden);
    Motor2.write(aantalgraden, 30, true);
}

void Robotarm::DraaiMotor3(uint8_t aantalgraden) {
    Motor3.write(aantalgraden, 30, true);
}

void Robotarm::DraaiMotor4(uint8_t aantalgraden) {
    Motor4.write(aantalgraden, 30, true);
}

/*---------------Uncomment dit wanneer grijper is aangesloten-------------------
void Robotarm::SluitKop() {
	//DraaiMotor5 wanneer deze wordt aangesloten voor de kop
	Motor5.write(45, 30, true);
}

void Robotarm::OpenKop() {
	//DraaiMotor5 wanneer deze wordt aangesloten voor de kop
	Motor5.write(45, 30, true);
}
void Robotarm::Grijpen(){
	SluitKop();
	delay(500);
	OpenKop();
	delay(500);
}
Omdat we nog geen grijper hebben is deze code ook nog niet getest, dit is simpel code voor het grijpen we gaan ervan uit dat het werkt
*/

void Robotarm::SluitKop() {
	//DraaiMotor5 wanneer deze wordt aangesloten voor de kop
}

void Robotarm::OpenKop() {
	//DraaiMotor5 wanneer deze wordt aangesloten voor de kop
}

void Robotarm::AlsGroterDan(uint8_t a, uint8_t b) {

}

void Robotarm::AlsKleinerDan(uint8_t a, uint8_t b) {

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

void Robotarm::dof2Move(float X, float Y){
	//dit is de 2 DOF versie van de inverse kinematica
	if(Y>X || Y==X){
		hoek2dof2 = acos( ( pow(X,2) + pow(Y,2) - pow(Arm_1,2) - pow(Arm_2dof2 , 2) ) / ( 2 * Arm_1 * Arm_2dof2 ) );
		hoek1dof2 = atan(Y/X) - atan( Arm_2dof2 * hoek2dof2 ) / (Arm_1 + cos(hoek2dof2)  * Arm_2dof2 ) ;
		
		hoek2dof2 = radToDeg(hoek2dof2);
		hoek1dof2 = radToDeg(hoek1dof2);
	} else{
		hoek2dof2 = -acos( ( pow(X,2) + pow(Y,2) - pow(Arm_1,2) - pow(Arm_2dof2 , 2) ) / ( 2 * Arm_1 * Arm_2dof2 ) );
		hoek1dof2 = atan(Y/X) + atan( Arm_2dof2 * hoek2dof2 ) / (Arm_1 + cos(hoek2dof2)  * Arm_2dof2 ) ;
		
		hoek2dof2 = radToDeg(hoek2dof2);
		hoek1dof2 = radToDeg(hoek1dof2);
	}
}
	//char Cijfer_str[1]; //Dit was bedoeld om int om te zetten naar string
	//sprintf(Cijfer_str, "%f", Cijfer);
	
/*Functie naarPunt is bedoeld om vaste posities op een grafiek te bereiken
alle vaste posities zijn gedefinieerd in de code, de leerling dient alleen een locatie te kiezen
Bijvoorbeeld: Locatie A hoogte 1, locatie A hoogte 2 locatie A hoogte 3 elke letter heeft 3 niveaus*/
	
void Robotarm::naarPunt(char letter, char cijfer){
	String cirkel1 = "ACEGIKMOQSUW"; //P.S:(''): dit wordt gezien als een char en ("") wordt gezien als een const char.
	String cirkel2 = "BDFHJLNPRTVX";
	if(cijfer == '1'){
		if(cirkel1.indexOf(letter) >= 0){
			if(letter=='A'){
				Motor1.write(22.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='C'){
				Motor1.write(45, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='E'){
				Motor1.write(67.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='G'){
				Motor1.write(112.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='I'){
				Motor1.write(135, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='K'){
				Motor1.write(157.5, 30, true); //rotatie
				delay(500);			
			}
			else if(letter=='M'){
				Motor1.write(202.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='O'){
				Motor1.write(225, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='Q'){
				Motor1.write(247.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='S'){
				Motor1.write(292.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='U'){
				Motor1.write(315, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='W'){
				Motor1.write(337.5, 30, true); //rotatie
				delay(500);
			}
	// ------------------------aanpassen voor armstand---------------------------------------++++++++++++++++++++++++++++++++++++++++++++++++++++++
			float aantalgraden = mirrorM(55);
			Motor2.write(aantalgraden, 30, false);
			// delay(500);
			Motor4.write(155, 40, false);
			// delay(500);
			Motor3.write(0, 40, false);
			delay(500);
			
	// --------------------------------------------------------------------------------------++++++++++++++++++++++++++++++++++++++++++++++++++++++
		}
		else if(cirkel2.indexOf(letter) >= 0){
			if(letter=='B'){
				Motor1.write(22.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='D'){
				Motor1.write(45, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='F'){
				Motor1.write(67.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='H'){
				Motor1.write(112.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='J'){
				Motor1.write(135, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='L'){
				Motor1.write(157.5, 30, true); //rotatie
				delay(500);			
			}
			else if(letter=='N'){
				Motor1.write(202.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='P'){
				Motor1.write(225, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='R'){
				Motor1.write(247.5, 30, true); //rotatie
				delay(500);			
			}
			else if(letter=='T'){
				Motor1.write(292.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='V'){
				Motor1.write(315, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='X'){
				Motor1.write(337.5, 30, true); //rotatie
				delay(500);
			}
// ------------------------aanpassen voor armstand---------------------------------------+++++++++++++++++++++++++++++++++++++++++++++++++++++
			Motor4.write(125, 40, false);
			// delay(500);
			Motor3.write(45, 40, false);
			// delay(500);
			float aantalgraden = mirrorM(40);
			Motor2.write(aantalgraden, 35, false);
			delay(500);
			
// ------------------------------------------
		}
	}
	else if(cijfer == '2'){
		Serial.println("Ik ben in cijfer 2");
		if(cirkel1.indexOf(letter) >= 0){
			if(letter=='A'){
				Motor1.write(22.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='C'){
				Motor1.write(45, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='E'){
				Motor1.write(67.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='G'){
				Motor1.write(112.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='I'){
				Motor1.write(135, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='K'){
				Motor1.write(157.5, 30, true); //rotatie
				delay(500);			
			}
			else if(letter=='M'){
				Motor1.write(202.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='O'){
				Motor1.write(225, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='Q'){
				Motor1.write(247.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='S'){
				Motor1.write(292.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='U'){
				Motor1.write(315, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='W'){
				Motor1.write(337.5, 30, true); //rotatie
				delay(500);
			}
	// ------------------------aanpassen voor armstand---------------------------------------++++++++++++++++++++++++++++++++++++++++++++++++++++++
			float aantalgraden = mirrorM(75);
			Motor2.write(aantalgraden, 30, false);
			// delay(500);
			Motor3.write(0, 40, false);
			// delay(500);
			Motor4.write(135, 40, false);
			delay(500);
			
	// --------------------------------------------------------------------------------------++++++++++++++++++++++++++++++++++++++++++++++++++++++
		}
		else if(cirkel2.indexOf(letter) >= 0){
			Serial.println("Ik ben in cijfer 2");
			if(letter=='B'){
				Serial.println("Ik ben in cijfer 2 punt B");
				Motor1.write(22.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='D'){
				Motor1.write(45, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='F'){
				Motor1.write(67.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='H'){
				Motor1.write(112.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='J'){
				Motor1.write(135, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='L'){
				Motor1.write(157.5, 30, true); //rotatie
				delay(500);			
			}
			else if(letter=='N'){
				Motor1.write(202.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='P'){
				Motor1.write(225, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='R'){
				Motor1.write(247.5, 30, true); //rotatie
				delay(500);			
			}
			else if(letter=='T'){
				Motor1.write(292.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='V'){
				Motor1.write(315, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='X'){
				Motor1.write(337.5, 30, true); //rotatie
				delay(500);
			}
// ------------------------aanpassen voor armstand---------------------------------------+++++++++++++++++++++++++++++++++++++++++++++++++++++
			float aantalgraden = mirrorM(50);
			Motor2.write(aantalgraden, 30, false);
			// delay(500);
			Motor3.write(50, 40, false);
			// delay(500);
			Motor4.write(115, 40, false);
			delay(500);
// ------------------------------------------
		}
	}
	else if(cijfer == '3'){
		if(cirkel1.indexOf(letter) >= 0){
			if(letter=='A'){
				Motor1.write(22.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='C'){
				Motor1.write(45, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='E'){
				Motor1.write(67.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='G'){
				Motor1.write(112.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='I'){
				Motor1.write(135, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='K'){
				Motor1.write(157.5, 30, true); //rotatie
				delay(500);			
			}
			else if(letter=='M'){
				Motor1.write(202.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='O'){
				Motor1.write(225, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='Q'){
				Motor1.write(247.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='S'){
				Motor1.write(292.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='U'){
				Motor1.write(315, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='W'){
				Motor1.write(337.5, 30, true); //rotatie
				delay(500);
			}
	// ------------------------aanpassen voor armstand---------------------------------------++++++++++++++++++++++++++++++++++++++++++++++++++++++
			float aantalgraden = mirrorM(80);
			Motor2.write(aantalgraden, 30, false);
			// delay(500);
			Motor3.write(45, 40, false);
			// delay(500);
			Motor4.write(85, 40, false);
			delay(500);
	// --------------------------------------------------------------------------------------++++++++++++++++++++++++++++++++++++++++++++++++++++++
		}
		else if(cirkel2.indexOf(letter) >= 0){
			if(letter=='B'){
				Motor1.write(22.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='D'){
				Motor1.write(45, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='F'){
				Motor1.write(67.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='H'){
				Motor1.write(112.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='J'){
				Motor1.write(135, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='L'){
				Motor1.write(157.5, 30, true); //rotatie
				delay(500);			
			}
			else if(letter=='N'){
				Motor1.write(202.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='P'){
				Motor1.write(225, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='R'){
				Motor1.write(247.5, 30, true); //rotatie
				delay(500);			
			}
			else if(letter=='T'){
				Motor1.write(292.5, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='V'){
				Motor1.write(315, 30, true); //rotatie
				delay(500);
			}
			else if(letter=='X'){
				Motor1.write(337.5, 30, true); //rotatie
				delay(500);
			}
// ------------------------aanpassen voor armstand---------------------------------------+++++++++++++++++++++++++++++++++++++++++++++++++++++

			Motor3.write(95, 30, false);
			// delay(500);
			float aantalgraden = mirrorM(45);
			Motor2.write(aantalgraden, 30, false);
			// delay(500);
			Motor4.write(65, 30, false);
			delay(500);
// ------------------------------------------
		}
	}
}

/* arm positioning routine utilizing inverse kinematics */
/* z is height, y is distance from base center out, x is side to side. y,z can only be positive */
//void set_arm( uint16_t x, uint16_t y, uint16_t z, uint16_t grip_angle )
void Robotarm::circle_method( float x, float y, float z, float grip_angle_d, int servoSpeed) {
	int BASE_HGT = 51; //base height
	int HUMERUS = 122; //shoulder-to-elbow "bone"
	int ULNA = 125; //elbow-to-wrist "bone"
	int GRIPPER = 50; //gripper (incl.heavy duty wrist rotate mechanism) length "
// #define ftl(x) ((x)>=0?(long)((x)+0.5):(long)((x)-0.5)) //float to long conversion
	float epsilon = 0.00001;
	
	float hum_sq = HUMERUS * HUMERUS;
	float uln_sq = ULNA * ULNA;
	

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
		// Serial.println("Error: Out of range!");
		return;
	} 
	else if (dist < abs(ULNA - HUMERUS)) {
		// Serial.println("Error: Too close!");
		return;
	} 
	else if ((dist == 0) and (ULNA == HUMERUS)) {
		// Serial.println("Error: Exactly the same so idk how u got this");
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

	// Serial.print("Wrist Point : (");
	// Serial.print(wrist_y);
	// Serial.print(",");
	// Serial.print(wrist_z);
	// Serial.println(")");

	//whichever intersection is more up
	if (zs1 > zs2) {
		elbow_z = zs1;
		elbow_y = ys1;
	} 
	else {
		elbow_z = zs2;
		elbow_y = ys2;
	}
	// Serial.print("Elbow Point : (");
	// Serial.print(elbow_y);
	// Serial.print(",");
	// Serial.print(elbow_z);
	// Serial.println(")");

	float shoulder_angle_d = degrees( atan2( abs(elbow_z - shoulder_z), abs(elbow_y - shoulder_y) ) );
	float elbow_angle_d =  -(degrees( atan2( abs(wrist_z - elbow_z), abs(wrist_y - elbow_y) ) ) - shoulder_angle_d );
	float wrist_angle_d = degrees( atan2(z - wrist_z, y - wrist_y)) - elbow_angle_d - shoulder_angle_d + 180;

	// Serial.print("Angles : ");
	// Serial.print(base_angle_d);
	// Serial.print(" ");
	// Serial.print(shoulder_angle_d);
	// Serial.print(" ");
	// Serial.print(elbow_angle_d);
	// Serial.print(" ");
	// Serial.println(wrist_angle_d);

	float aantalgraden1 = mirrorM(base_angle_d + 180);
	float aantalgraden2 = mirrorM(shoulder_angle_d);
	float aantalgraden3 = mirrorM(180 - elbow_angle_d);
	float aantalgraden4 = mirrorM(180 - wrist_angle_d);		

	Motor1.write(aantalgraden1, servoSpeed); //anti negatives direction fix
	Motor2.write(aantalgraden2, servoSpeed);
	Motor3.write(aantalgraden3, servoSpeed); //diretion fix
	Motor4.write(aantalgraden4, servoSpeed); //direction fix
	return;
}