#include <Robotarm.h>
Robotarm arm;


void setup()// Hier worden functies geplaatst die maar één keer worden uitgevoerd
{
  Serial.begin(9600);
  //Serial.setTimeout(3);// 1000 ms is 1 s
  arm.attach();
  Serial.println("Herstel");
  arm.HerstelServos();// Zet de arm terug naar de oorspronkelijke positie
  delay(500);
  arm.X  = 0.0;
  arm.Y  = 9.0;
  Serial.println("Nu gaan");
  //arm.BerekenAantalGraden(arm.X, arm.Y);
  arm.dof2Move(arm.X,arm.Y);
  Serial.print("Hoek 1: ");
  Serial.println(arm.hoek1dof2);
  Serial.print("Hoek 2: ");
  Serial.println(arm.hoek2dof2);
//  Serial.print("Hoek 3: ");
//  Serial.println(arm.Hoek3);
  arm.DraaiMotor2(arm.hoek1dof2);  
  arm.DraaiMotor3(arm.hoek2dof2);
//  arm.DraaiMotor4(arm.Hoek3);
  Serial.println("------------------------------------------------------------------------------------------");
  
}

void loop()// Hier worden functies geplaatst die herhaald worden
{

  //if (Serial.available() > 0){

    //Serial.println("Geef aan welke getal je wilt bereiken: ");

 // }

//  arm.DraaiMotor1(180);
//  delay(1000);
//  arm.DraaiMotor2(45);
//  delay(1000);
//  arm.DraaiMotor3(40);
//  delay(1000);
//  arm.DraaiMotor4(90);
//  delay(1000);
}

  
  
//  Serial.print("phi= ");
//  Serial.println(arm.phi);
//  Serial.print("wx = ");
//  Serial.println(arm.wx);
//  Serial.print("wy= ");
//  Serial.println(arm.wy);
//
//  Serial.print("delta= ");
//  Serial.println(arm.delta);
//  Serial.print("c2= ");
//  Serial.println(arm.c2);
//  Serial.print("s2= ");
//  Serial.println(arm.s2);
//  Serial.print("theta_2= ");
//  Serial.println(arm.theta_2);
//
//  Serial.print("s1= ");
//  Serial.println(arm.s1);
//  Serial.print("c1= ");
//  Serial.println(arm.c1);
//  Serial.print("theta_1= ");
//  Serial.println(arm.theta_1);
//  Serial.print("theta_3= ");
//  Serial.println(arm.theta_3);
