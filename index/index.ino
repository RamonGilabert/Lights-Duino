#include <RBL_nRF8001.h>
#include <RBL_services.h>
#include <aci.h>
#include <aci_cmds.h>
#include <aci_evts.h>
#include <aci_protocol_defines.h>
#include <aci_queue.h>
#include <aci_setup.h>
#include <acilib.h>
#include <acilib_defs.h>
#include <acilib_if.h>
#include <acilib_types.h>
#include <ble_assert.h>
#include <boards.h>
#include <bootloader_setup.h>
#include <dtm.h>
#include <hal_aci_tl.h>
#include <hal_platform.h>
#include <lib_aci.h>

#include <SoftwareSerial.h>

unsigned int timeout = 0;
unsigned char state = 0;
 
byte information[3];
int informationLED = 7;
int redLED = 10;
int greenLED = 11;
int blueLED = 12;

void setup() {
  Serial.begin(57600);

  pinMode(informationLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  pinMode(0, INPUT);

  ble_begin();
}

void loop() {
  if (ble_available()) {
    for (int i = 0; i <= 2; i++) {
      information[i] = ble_read(); 
    }

    analogWrite(redLED, information[0]);
    analogWrite(greenLED, information[1]);
    analogWrite(blueLED, information[2]);
  }
}

