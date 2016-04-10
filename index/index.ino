#include <SPI.h>
#include <EEPROM.h>
#include <boards.h>
#include <RBL_nRF8001.h>

#include <SoftwareSerial.h>

unsigned int timeout = 0;
unsigned char state = 0;
 
byte information[3];
int informationLED = 7;
int redLED = 3;
int greenLED = 5;
int blueLED = 6;

void setup() {
  pinMode(informationLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  analogWrite(redLED, 0);
  analogWrite(greenLED, 0);
  analogWrite(blueLED, 0);

  pinMode(0, INPUT);

  ble_begin();
}

void loop() {
  if (ble_available() == 3) {
    analogWrite(redLED, ble_read());
    analogWrite(greenLED, ble_read());
    analogWrite(blueLED, ble_read());
  }

  ble_do_events();
}

