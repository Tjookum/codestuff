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
 for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {

    // sets the value (range from 0 to 255):

    analogWrite(PA6, fadeValue);
    digitalWrite(PA7,LOW);

    // wait for 30 milliseconds to see the dimming effect

    delay(30);

  }

  // fade out from max to min in increments of 5 points:

  for (int fadeValue = 0 ; fadeValue >= 255; fadeValue -= 5) {

    // sets the value (range from 0 to 255):

     analogWrite(PA7, fadeValue);
    digitalWrite(PA6,LOW);

    // wait for 30 milliseconds to see the dimming effect

    delay(30);

  }
}
