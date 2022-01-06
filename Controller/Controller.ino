#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"


const int analogInPin0 = A0;  // Analog input pin that the potentiometer is attached to
const int analogInPin1 = A1;  // Analog input pin that the potentiometer is attached to

int sensorValue0 = 0;        // value read from the pot
int sensorValue1 = 0;        // value read from the pot

RF24 radio(7, 8);
// Single radio pipe address for the 2 nodes to communicate.
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup() {
  Serial.begin(9600);
  printf_begin();
  //role = role_remote
  radio.begin();
  radio.openWritingPipe(pipe);
  radio.printDetails();
  
}

void loop() {
  sensorValue0 = analogRead(analogInPin0);
  sensorValue1 = analogRead(analogInPin1);
  String val0=(String)sensorValue0;
  String val1=(String)sensorValue1;
  String mess="S";
  int tmp=951;
  
  //Serial.print(sensorValue0);
  //Serial.print(";");
  //Serial.print(sensorValue1);
  //Serial.print(";");
  //Serial.println(millis());
  //printf("Now sending...");
  
  //bool ok = radio.write( &sensorValue0, sizeof(sensorValue0));
  bool ok = radio.write( &tmp, sizeof(tmp));
  ok = radio.write( &mess, sizeof(mess));
  if (ok)
    printf("ok\n\r");
  else
    printf("failed\n\r");
    delay(20);
}
