#include <SoftwareSerial.h>

unsigned int timeout = 0;
unsigned char state = 0;
 
byte information[3];
int informationLED = 7;
int redLED = 10;
int greenLED = 11;
int blueLED = 12;

ISR(TIMER2_OVF_vect) { 
  TCNT2 = 0;
  timeout++;
  
  if (timeout > 61) {
    state=1;
    timeout=0;
  }
}
 
void init_timer2(void) {
  TCCR2A |= (1 << WGM21) | (1 << WGM20);   
  TCCR2B |= 0x07;
  ASSR |= (0<<AS2);
  TIMSK2 |= 0x01;
  TCNT2 = 0;
  sei();   
}

void setup() {
  Serial.begin(9600);

  pinMode(informationLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  pinMode(0, INPUT);
 
  attachInterrupt(0, cleantime, FALLING);
  init_timer2();
}

void control(void) {
  if (Serial.available() == 3) {
    for (int i = 0; i <= 2; i++) {
      information[i] = Serial.read(); 
    }

    analogWrite(redLED, information[0]);
    analogWrite(greenLED, information[1]);
    analogWrite(blueLED, information[2]);
  }
}

void loop() {
  switch(state) {
    case 0:
      break;
    case 1:
      control(); 
      break;
  }
}
 
void cleantime() {
  timeout = 0;
  state = 0;
}

