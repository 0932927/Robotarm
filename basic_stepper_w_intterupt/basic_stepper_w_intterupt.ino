#define ledPin 13
#define A 8
#define B 9
#define C 10
#define D 11
int x=0;
int doOnce = 1;
int angle = 0.0;
int oneStepComplete=0;
int stepperangleInt = 0;
float stepperangle = 0;
float input;

void setup(){
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(D,OUTPUT);
  Serial.begin(115200);
  
  // initialize timer1 
  cli();         // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 16000000/256/400;            // compare match register 16MHz/prescaler/2Hz hz kan van 0-500
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  //TCCR1B |= (1 << CS10);    // CS12+ CS10=1024 prescaler 
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  sei();            // enable all interrupts  
}

ISR(TIMER1_COMPA_vect)   {       // timer compare interrupt service routine
  //digitalWrite(ledPin, digitalRead(ledPin) ^ 1);   // toggle LED pin
  onestep();
}

void write(int a,int b,int c,int d){
  digitalWrite(A,a);
  digitalWrite(B,b);
  digitalWrite(C,c);
  digitalWrite(D,d);
}

void onestep(){
  // 512 keer deze functie is 360 graden gedraaid
  // stride angle 5.625/64 met een gear ratio van 1:64
  // 360/5.625 = 64 door gearbox krijg je 64*64 dus je hebt 4096 steps in half step mode
  // dit beteken 2048 steps in full step mode
  // wanner we deze functie 1 keer uitvoeren zetten we 4 steps 2048 / 4 = 512
  // dit betekent dat je dus 512 keer deze functie uitvoert voor een volledige rotatie
  if(oneStepComplete <= degreeToSteps(angle)){
    switch(x){
      case 0:
        write(1,0,0,0);
        x++;
        break;
  
      case 1:
        write(0,1,0,0);
        x++;
        break;
  
      case 2:
        write(0,0,1,0);
        x++;
        break;
  
      case 3:
        write(0,0,0,1);
        x = 0;
        oneStepComplete++; // per keer dat je hier komt is de motor 0,703125 gedraaid
        stepperangle = stepperangle + 0.703125;
        stepperangleInt = (int)stepperangle % 360;
        Serial.print("Stepper hoek float: ");
        Serial.println(stepperangle);
        Serial.print("Stepper hoek int: ");
        Serial.println(stepperangleInt);
        break;
  
    }
  }else{
    write(0,0,0,0);
  }
  
  
}

void onestepBasic(){
  // half steps currently
  write(1,0,0,0);
  delay(5);
  write(1,1,0,0);
  delay(5);
  write(0,1,0,0);
  delay(5);
  write(0,1,1,0);
  delay(5);
  write(0,0,1,0);
  delay(5);
  write(0,0,1,1);
  delay(5);
  write(0,0,0,1);
  delay(5);
  write(1,0,0,1);
  delay(5);
}

int degreeToSteps(float hoek){
  float degreePerStep = 360.0/512.0;
  float numOfSteps = hoek/degreePerStep;
  return (int)numOfSteps;
}

void loop(){

  if(Serial.available()){
    input = Serial.parseFloat();
    if (input != 0.0){
      angle = input;
      oneStepComplete=0;
    }
    //hoek = (int)input;
  }

//  if (doOnce==1){
//    Serial.println("kak");
//    for(int z=0; z<=512; z++){
//      Serial.println("infor");
//      onestepBasic();
//      Serial.println(z);
//    }
//    doOnce = 0;
//  }
}
