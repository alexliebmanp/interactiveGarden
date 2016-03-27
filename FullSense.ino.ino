//
//    FullSense.ino - a test for incorporating sensing and sound/light response. 
//


#include <SoftwareSerial.h>
#include "Adafruit_Soundboard.h"
#include <CapacitiveSensor.h>

// choose any two pins on Arduino to use for serial communication.
#define SFX_TX 5
#define SFX_RX 6

// connect to the RST pin on the soundboard for any resetting purposes on sound board.
#define SFX_RST 4

// create instance of software serial.
SoftwareSerial ss = SoftwareSerial(SFX_TX,SFX_RX);

// pass serial to Adafruit soundboard.
Adafruit_Soundboard soundboard = Adafruit_Soundboard(&ss,NULL,SFX_RST);

// Define constants for capacitive sensing
int sendPin = 11;
int sensePin = 10;
double threshold = 1000;

// create instance of capacitive sensor
CapacitiveSensor plant(sendPin, sensePin);  // _ resistor with no capacitor in parallel. 

// define constants for light control
int lightPin = 3;


void setup() {
  Serial.begin(115200);
  ss.begin(9600);

  if (!soundboard.reset()) {
    Serial.println("Sound board not found");
    while (1);
  }
  Serial.println("Sound board found");

  plant.set_CS_AutocaL_Millis(10);       // set the calibration wait period in ms.
                                         // - makes the signal very stable but less sensitive.

  // setup light control pin and set it high by defualt.
  pinMode(lightPin,OUTPUT);
  digitalWrite(lightPin,HIGH);

  // for demo purposes, start with sound playing.
  soundboard.playTrack(1);
  
}

void loop() {

 long sensorValue = plant.capacitiveSensor(80);

 // for debugging purposes: do not output normally or you will fuck 
 // up the midi message. 
 Serial.println(sensorValue);

 if (sensorValue > threshold) {
  soundboard.pause();
  digitalWrite(lightPin,LOW);
  
 }
 else {
   soundboard.unpause();
   digitalWrite(lightPin,HIGH); 
 }
 
}
