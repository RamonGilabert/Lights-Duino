#include <SoftwareSerial.h>

unsigned int timeout = 0;
unsigned char state = 0;
 
byte information[3];
int informationLED = 7;
int redLED = 10;
int greenLED = 11;
int blueLED = 12;

void setup() {
  Serial.begin(9600);

  pinMode(informationLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  pinMode(0, INPUT);
}

void loop() {
  if (Serial.available() == 3) {
    for (int i = 0; i <= 2; i++) {
      information[i] = Serial.read(); 
    }

    analogWrite(redLED, information[0]);
    analogWrite(greenLED, information[1]);
    analogWrite(blueLED, information[2]);
  }
}

