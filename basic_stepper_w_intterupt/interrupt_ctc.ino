//#define ledPin 13
//#define A 8
//#define B 9
//#define C 10
//#define D 11
//int x = 0;
//
//void setup(){
//  pinMode(ledPin, OUTPUT);
//  pinMode(A,OUTPUT);
//  pinMode(B,OUTPUT);
//  pinMode(C,OUTPUT);
//  pinMode(D,OUTPUT);
//  // initialize timer1 
//  cli();         // disable all interrupts
//  TCCR1A = 0;
//  TCCR1B = 0;
//  TCNT1  = 0;
//  OCR1A = 16000000/256/100;            // compare match register 16MHz/prescaler/2Hz
//  TCCR1B |= (1 << WGM12);   // CTC mode
//  TCCR1B |= (1 << CS12);    // 256 prescaler 
//  //TCCR1B |= (1 << CS10);    // CS12+ CS10=1024 prescaler 
//  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
//  sei();            // enable all interrupts
//}
//
//ISR(TIMER1_COMPA_vect)   {       // timer compare interrupt service routine
//  //digitalWrite(ledPin, digitalRead(ledPin) ^ 1);   // toggle LED pin
//  onestep();
//
//}
//
//void write(int a,int b,int c,int d){
//  digitalWrite(A,a);
//  digitalWrite(B,b);
//  digitalWrite(C,c);
//  digitalWrite(D,d);
//}
//
//void onestep(){
//  switch(x){
//    case 0:
//      digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
//      write(1,0,0,0);
//      x++;
//      break;
//  //  delay(5);
//  //  write(1,1,0,0);
//  //  delay(5);
//    case 1:
//      digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
//      write(0,1,0,0);
//      x++;
//      break;
//  //  delay(5);
//  //  write(0,1,1,0);
//  //  delay(5);
//    case 2:
//      digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
//      write(0,0,1,0);
//      x++;
//      break;
//  //  delay(5);
//  //  write(0,0,1,1);
//  //  delay(5);
//    case 3:
//      digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
//      write(0,0,0,1);
//      x = 0;
//      break;
//  //  delay(5);
//  //  write(1,0,0,1);
//  //  delay(5);
//  }
//}
//
//void loop(){
//  //onestep();
//  Serial.println(x);
//  // your program here…
//}
