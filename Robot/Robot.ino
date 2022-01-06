#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

RF24 radio(9, 10);
// Single radio pipe address for the 2 nodes to communicate.
const uint64_t pipe = 0xE8E8F0F0E1LL;

// Pins on the remote for buttons
const uint8_t button_pins[] = { 2, 3, 4, 5, 6, 7 };
const uint8_t num_button_pins = sizeof(button_pins);

// Pins on the LED board for LED's
const uint8_t led_pins[] = { 2, 3, 4, 5, 6, 7 };
const uint8_t num_led_pins = sizeof(led_pins);

uint8_t button_states[10];
uint8_t led_states[num_led_pins];



String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
char mode='s';

void setup() {
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600);
    printf_begin();
    inputString.reserve(200);

    radio.begin();
    radio.openReadingPipe(1, pipe);
    radio.startListening();
}


// the loop function runs over and over again forever
void loop() {
    // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString);
    // clear the string:
    mode=inputString[0];
    inputString = "";
    stringComplete = false;
    
  }
//printf("Got buttons\n\r");
    if ( radio.available() )
    {
     // printf("Got buttons\n\r");
      // Dump the payloads until we've gotten everything
      while (radio.available())
      {
        // Fetch the payload, and see if this was the last one.
        radio.read( button_states, num_button_pins );
        //Variable[] val={button_states[0],button_states[1]};
       //String mess=(String)button_states;
        // Spew it
        //printf("Got buttons\n\r");
        Serial.print(button_states[0]);
        Serial.print(button_states[1]);
        Serial.print(button_states[2]);
        Serial.print(button_states[3]);
        Serial.print(button_states[4]);
        Serial.print(button_states[5]);
        Serial.print(button_states[6]);
        Serial.print(button_states[7]);
        Serial.print(button_states[8]);
        Serial.print(button_states[9]);
        Serial.println(button_states[10]);
      }
    }
  delay(500);
 switch (mode) {
  case 's':
    Stop();
    break;
  case 'f':
    Forward();
    break;
   case 'b':
    Back();
    break;
   case 'l':
    Left();
    break;
   case 'r':
    Right();
    break;
  default:
    Stop();
    break; }

   //delay(10);                       // wait for a second
}

void Stop(){
  digitalWrite(3, LOW);   
  digitalWrite(5, LOW);  
  digitalWrite(6, LOW);   
  digitalWrite(7, LOW);  
}

void Forward(){
  digitalWrite(3, HIGH);  
  digitalWrite(5, LOW);   
  digitalWrite(6, HIGH);  
  digitalWrite(7, LOW);   
}

void Back(){
  digitalWrite(3, LOW);  
  digitalWrite(5, HIGH); 
  digitalWrite(6, LOW); 
  digitalWrite(7, HIGH);   
}

void Right(){
  digitalWrite(3, LOW);   
  digitalWrite(5, HIGH);   
  digitalWrite(6, HIGH);  
  digitalWrite(7, LOW);  
}

void Left(){
  digitalWrite(3, HIGH);   
  digitalWrite(5, LOW);   
  digitalWrite(6, LOW);   
  digitalWrite(7, HIGH);   
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
