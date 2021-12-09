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
  
  arm.naarPunt('A','1');
  delay(1000);
  arm.naarPunt('B','1');
  delay(1000);
  arm.naarPunt('C','1');
  delay(1000);
  arm.naarPunt('D','1');
  delay(1000);
  arm.naarPunt('E','1');
  delay(1000);
  arm.naarPunt('F','1'); 
    delay(1000);
  arm.naarPunt('G','1');
  delay(1000);
  arm.naarPunt('H','1');
  delay(1000);
  arm.naarPunt('I','1'); 
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
