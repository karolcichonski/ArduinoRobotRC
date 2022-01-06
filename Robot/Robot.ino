/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
char mode='s';
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600);
    inputString.reserve(200);
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
