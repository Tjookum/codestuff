/*************************************************************
  Wheel of Life V2 noWifi
  artist: Madelon Hooykaas
  Programmer: Jochem van Grieken
  All rights reserved 08-2021
 *************************************************************/
#include <Arduino.h>

//built in ledpin
const int ledPin = 2;

//PIR sensor
const int pirPin = 13;
bool pirState = false;



//VFD variables
const int VFDStartPin = 25;
const int VFDIsRunning = 33;
bool motorFinished = false;
bool motorState = true;

//Audio variables
const int triggerPin = 26;
bool triggerState = true;
const int isPlayingPin = 27;
bool audioFinished = true;
bool isPlaying = true;

int showCount = 0;
int totalShowCount;
int oldShowcount = 0;
const int motorInterval = 60000;
const int triggerInterval = 5000;

unsigned long currentMillis = 0;
unsigned long previousMillisMotorTimer = 0;
unsigned long previousMillisTriggerTimer = 0;

void setup()
{
  // Debug console
  Serial.begin(9600);

  //pinmode definitions
  pinMode(VFDStartPin, OUTPUT);
  pinMode(VFDIsRunning, INPUT_PULLUP);
  pinMode(triggerPin, OUTPUT);
  pinMode(isPlayingPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT_PULLDOWN);
}

void checkPir()
{
  if (digitalRead(pirPin) && !pirState)
  {
    pirState = true;
    Serial.println("pir has been triggered");
  }
  else if (pirState && showCount != oldShowcount)
  {
    pirState = false;
    oldShowcount = showCount;
    Serial.println("one show is finished, checking pir again");
  }
}

void playaudio()
{
  if (isPlaying){ Serial.println("playing audio");}
  digitalWrite(triggerPin, isPlaying);
  delay(triggerInterval);
  isPlaying = false;
  

  if (!isPlaying && !digitalRead(isPlayingPin))
  {
    Serial.println("audio file is finished");
    audioFinished = true;
    motorFinished = false;
    motorState = true;
    showCount ++;
    totalShowCount ++;
  }
}
void runmotor()
{
  if (motorState){ Serial.println("turning motor");}
    digitalWrite(VFDStartPin, motorState);
    delay(motorInterval);
    motorState = false;

  

  if (!motorState && !digitalRead(VFDIsRunning))
  {
    Serial.println("motor is finished");
    motorFinished = true;
    audioFinished = false;
    isPlaying = true;

  }
}

void loop()
{

  //currentMillis = millis();
  checkPir();
  if (pirState)
  {

    if (!audioFinished && motorFinished)
    {
      playaudio();
    }
    else if (!motorFinished && audioFinished)
    {
      runmotor();
    }
  }  
}
