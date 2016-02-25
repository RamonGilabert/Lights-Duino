unsigned int timeout = 0;
unsigned char state = 0;
 
char information;
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
 
// initialize the timer 2 service
void init_timer2(void) {
  TCCR2A |= (1 << WGM21) | (1 << WGM20);   
  TCCR2B |= 0x07;                         // by clk/1024
  ASSR |= (0<<AS2);                       // Use internal clock - external clock not used in Arduino
  TIMSK2 |= 0x01;                         //Timer2 Overflow Interrupt Enable
  TCNT2 = 0;
  sei();   
}

void setup() {
  Serial.begin(9600);

  pinMode(informationLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  pinMode(2, INPUT);
 
  attachInterrupt(0, cleantime, FALLING);
  init_timer2();
}

void control(void) {
  if (Serial.available()) {
    val = Serial.read();
  }

  printf(val);
  
  val = ' ';
    
  delay(100);
}

// control loop for the program
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