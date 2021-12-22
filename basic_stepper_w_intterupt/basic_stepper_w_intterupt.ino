#define A 8
#define B 9
#define C 10
#define D 11
int x=0, y=0;
int angle = 0;
int oneStepComplete=0;
int stepperangleInt = 0;
float stepperangle = 0;
float input;
int linksRechts = 0; // 1 is rechtsom 0 is linksom


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
  
  if( (hoekverschil() > 0) && (linksRechts == 1 )){
  //rechtsom
    switch(y){
      case 0:
        write(1,0,0,0);
        y++;
        break;
  
      case 1:
        write(0,1,0,0);
        y++;
        break;
  
      case 2:
        write(0,0,1,0);
        y++;
        break;
  
      case 3:
        write(0,0,0,1);
        y = 0;
        oneStepComplete++; // per keer dat je hier komt is de motor 0,703125 gedraaid
        stepperangle = stepperangle + 0.703125;
        stepperangleInt = (int)stepperangle % 360;
        Serial.print("Stepper hoek float: ");
        Serial.println(stepperangle);
        Serial.print("Stepper hoek int: ");
        Serial.println(stepperangleInt);
        break;
  
    }
  }else if( (hoekverschil() > 0) && (linksRechts == 0 )){
  //linksom
    switch(x){
      case 0:
        write(0,0,0,1);
        x++;
        break;
  
      case 1:
        write(0,0,1,0);
        x++;
        break;
  
      case 2:
        write(0,1,0,0);
        x++;
        break;
  
      case 3:
        write(1,0,0,0);
        x = 0;
        oneStepComplete++; // per keer dat je hier komt is de motor 0,703125 gedraaid
        stepperangle = stepperangle - 0.703125;
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

int hoekverschil(){
  if(stepperangleInt < angle){
    linksRechts = 1; // true is links false is rechts
    //Serial.println("hoi");
    return angle - stepperangleInt ;
    
  }else if(stepperangleInt > angle){
    //Serial.println("doie");
    linksRechts = 0;
    return stepperangleInt - angle;  
  } else if(stepperangleInt == angle){
    linksRechts = 2;
  }
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
}
