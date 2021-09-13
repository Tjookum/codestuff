#include <Arduino.h>


// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  
  pinMode(PA6, OUTPUT);
  pinMode(PA7, OUTPUT);
  pinMode(PB12, OUTPUT);
  pinMode(PC13, OUTPUT);
  pinMode(PB14, OUTPUT);
  pinMode(PB15, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
digitalWrite(PA6,HIGH);
digitalWrite(PA7, LOW);
digitalWrite(PC13, HIGH);
delay(1000);
digitalWrite(PA6,LOW);
digitalWrite(PA7, HIGH);
digitalWrite(PC13, LOW);
delay(1000);

}
