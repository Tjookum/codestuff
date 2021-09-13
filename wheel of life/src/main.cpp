/*************************************************************
  Wheel of Life 
  artist: Madelon Hooykaas
  Programmer: Jochem van Grieken
  All rights reserved 08-2021


  
  githubtest
  3
 *************************************************************/
#include <Arduino.h>
#define BLYNK_PRINT Serial

// #define BLYNK_TEMPLATE_ID "TMPLglejJL4x"
// #define BLYNK_DEVICE_NAME "tester"


//Blynk wifi parameters
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
//char auth[] = "NJT07Z0oVqiqsbLnnGefskpcRnsAW_so";

//fill in credentials

char ssid[] = "";
char pass[] = "";
char auth[] = "NJT07Z0oVqiqsbLnnGefskpcRnsAW_so";

//built in ledpin
const int ledPin = 2;

//PIR sensor
const int pirPin = 13;
bool pirState = false;

BlynkTimer timer;

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
int motorInterval;
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

  //Blynk startup and timer initialization
  Blynk.begin(auth, ssid, pass);
  //Blynk.virtualWrite(V0, motorInterval);
}
BLYNK_CONNECTED()
{
  Blynk.syncVirtual(V0, V2);
}

BLYNK_WRITE(V0)
{
  motorInterval = param.asInt()*1000;
}
BLYNK_WRITE(V2)
{
  totalShowCount = param.asInt();
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
  timer.setTimeout(triggerInterval, []()
  { 
    isPlaying = false;
  });
  digitalWrite(triggerPin, isPlaying);

  if (!isPlaying && !digitalRead(isPlayingPin))
  {
    Serial.println("audio file is finished");
    audioFinished = true;
    motorFinished = false;
    motorState = true;
  }
}
void runmotor()
{
  if (motorState){ Serial.println("turning motor");}
  timer.setTimeout(motorInterval, []()
  { 
    motorState = false;
  });
  digitalWrite(VFDStartPin, motorState);

  if (!motorState && !digitalRead(VFDIsRunning))
  {
    Serial.println("motor is finished");
    motorFinished = true;
    audioFinished = false;
    isPlaying = true;
    showCount ++;
    totalShowCount ++;
  }
}

void loop()
{

  //currentMillis = millis();
  checkPir();
  if (pirState)
  {
      Blynk.run();
      timer.run();

    if (!audioFinished && motorFinished)
    {
      playaudio();
    }
    else if (!motorFinished && audioFinished)
    {
      runmotor();
    }
    Blynk.virtualWrite(V1, showCount);
    Blynk.virtualWrite(V2, totalShowCount);
  }  
}
