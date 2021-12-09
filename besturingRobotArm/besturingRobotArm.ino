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
//  
//  arm.Cijfer = '2'; // Veranderd het getal tussen de twee haakpunten
//  arm.Letter = 'A'; // Veranderd de letter tussen de twee haakpunten
//  arm.naarPunt(arm.Letter, arm.Cijfer);  
  
  arm.naarPunt('B','3');
  delay(1000);
  arm.naarPunt('A','3');
  delay(1000);
  arm.naarPunt('A','3');
}
void loop()// Hier worden functies geplaatst die herhaald worden
{


//  arm.DraaiMotor1(90);
//  delay(500);
//  arm.DraaiMotor2(0);
//  delay(500);
//  arm.DraaiMotor3(90);
//  delay(500);
//  arm.DraaiMotor4(90);
//  delay(500);

  }
