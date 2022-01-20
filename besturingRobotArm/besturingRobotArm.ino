#include <Robotarm.h>
Robotarm arm;

ISR(TIMER0_COMPA_vect)   {       // timer compare interrupt service routine
  arm.moveStepper(arm.stepperHoek);
}

float input;
int once = 1;
unsigned long currentMillis = 0;
void setup()// Hier worden functies geplaatst die maar één keer worden uitgevoerd
{ 

  Serial.begin(115200);
  //Serial.setTimeout(3);// 1000 ms is 1 s
  arm.attach();
  Serial.println("Herstel");
  arm.HerstelServos();// Zet de arm terug naar de oorspronkelijke positie
  Serial.println("Ready");

//   arm.circle_method(0, 200, 100, 0);
//  delay(500);
//  
//  arm.Cijfer = '2'; // Veranderd het getal tussen de twee haakpunten
//  arm.Letter = 'A'; // Veranderd de letter tussen de twee haakpunten
//  arm.naarPunt(arm.Letter, arm.Cijfer);  
    
//  arm.naarPunt('A','1');
//  delay(1000);
//  arm.naarPunt('K','3');
//    Serial.println(arm.stepperHoek);
//  delay(3000);
//  arm.naarPunt('C','3');
//  delay(3000);
//  arm.naarPunt('D','3');
//  delay(3000);
//  arm.naarPunt('E','3');
//  delay(3000);
//  arm.naarPunt('F','3'); 
//    delay(3000);
//  arm.naarPunt('G','3');
//  delay(3000);
//  arm.naarPunt('H','3');
//  delay(3000);
//  arm.naarPunt('I','3'); 
//  arm.circle_method(0, 200, 100, 0);
//  delay(10000);
//  arm.circle_method(-200, 100, 100, 0);
//  delay(10000);
}
void loop()// Hier worden functies geplaatst die herhaald worden
{
  currentMillis = millis();
 if(currentMillis > 1500){
    if (once == 1){
     arm.DraaiMotor2(0);
     delay(1000);
     arm.DraaiMotor2(180);
//omtrek voor 180 graden is ongeveer 1 meter
      once = 0;
    }
 }
//    arm.naarPunt('A','1');
//    delay(1000);
//    arm.naarPunt('K','3');
//    delay(1000);
//    arm.DraaiMotor2(80);
//  arm.DraaiMotor3(45);
//  Serial.println(arm.hoekverschil(arm.stepperHoek));
//  Serial.println(arm.linksRechtsStepper);
//  Serial.println(arm.stepperHoek);
//  arm.DraaiMotor1(90);
//  delay(500);
//  arm.DraaiMotor2(75);
//  arm.DraaiMotor3(120);
//  arm.DraaiMotor4(20);

//  delay(500);
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
//
if(Serial.available()){
    input = Serial.parseFloat();
    if (input != 0.0){
      arm.stepperHoek = input;
      Serial.println(arm.stepperHoek);
    }
  }
}
