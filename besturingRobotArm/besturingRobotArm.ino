#include <Robotarm.h>
Robotarm arm;
float input;

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
    
//  arm.naarPunt('A','3');
//  delay(1000);
//  arm.naarPunt('B','3');
//  delay(1000);
//  arm.naarPunt('C','3');
//  delay(1000);
//  arm.naarPunt('D','3');
//  delay(1000);
//  arm.naarPunt('E','3');
//  delay(1000);
//  arm.naarPunt('F','3'); 
//    delay(1000);
//  arm.naarPunt('G','3');
//  delay(1000);
//  arm.naarPunt('H','3');
//  delay(1000);
//  arm.naarPunt('I','3'); 
//  arm.circle_method(0, 200, 100, 0, 10);
//  delay(10000);
//  arm.circle_method(-200, 100, 100, 0, 10);
//  delay(10000);
}
void loop()// Hier worden functies geplaatst die herhaald worden
{
//  Serial.println(arm.hoekverschil(arm.stepperHoek));
//  Serial.println(arm.stepperangleInt);
//  Serial.println(arm.linksRechtsStepper);
//  Serial.println(arm.stepperHoek);
//  arm.DraaiMotor1(90);
//  delay(500);
  arm.DraaiMotor2(80);
  delay(500);
//  arm.DraaiMotor3(90);
//  delay(500);
//  arm.DraaiMotor4(90);
//  delay(500);

//  arm.write(1,0,0,0);
//  delay(5);
////  write(1,1,0,0);
////  delay(5);
//  arm.write(0,1,0,0);
//  delay(5);
////  write(0,1,1,0);
////  delay(5);
//  arm.write(0,0,1,0);
//  delay(5);
////  write(0,0,1,1);
////  delay(5);
//  arm.write(0,0,0,1);
//  delay(5);
////  write(1,0,0,1);
////  delay(5);

if(Serial.available()){
    input = Serial.parseFloat();
    if (input != 0.0){
      arm.stepperHoek = input;
    }
    //hoek = (int)input;
  }
}

ISR(TIMER0_COMPA_vect)   {       // timer compare interrupt service routine
  arm.onestep(arm.stepperHoek);
}
