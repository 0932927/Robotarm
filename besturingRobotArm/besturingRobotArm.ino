#include <Robotarm.h>
Robotarm arm;


void setup()// Hier worden functies geplaatst die maar één keer worden uitgevoerd
{
  Serial.begin(9600);
  //Serial.setTimeout(3);// 1000 ms is 1 s
  arm.attach();
  arm.HerstelServos();// Zet de arm terug naar de oorspronkelijke positie
  delay(2000);
  
  arm.X  = 10.0;
  arm.Y  = 15.0;
  arm.BerekenAantalGraden(arm.X, arm.Y);
  Serial.print("Hoek 1: ");
  Serial.print(arm.Hoek1);
  Serial.print(" Hoek 2: ");
  Serial.print(arm.Hoek2);
  Serial.print(" Hoek 3: ");
  Serial.print(arm.Hoek3);
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
