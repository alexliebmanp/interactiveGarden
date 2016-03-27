//
//  SoundSense.ino - this code is a test of serial communication 
//                   between the Arduino and the Adafruit Sound Board.
//                   The goal is to show that we can arbitrarily control the board.
//                   Feel free to add 
//
//                  - Connect the Arduino to soundboard at least on TX, RX, and RST pins.
//                  - Also ground UG pin on soundboard in order to set it to serial mode.
//
//                   The following commands can be used to control soundboard:
//                      1.  reset()                         reset the board to stable state
//                      2.  listFiles()                     gives a list of all the files
//                      3.  playTrack(n)                    play nth track in list
//                      4.  playTrack(name)                 play track with name name
//                      5.  volUp()                         volume up
//                      6.  volDown()                       volume down
//                      7.  pause()                         pause
//                      8.  unpause()                       ...
//                      9.  stop()                          ...
//                      10. trackTime(&current, &total)     gives track time. Note we are passing references
//                      11. trackSize(&remain, &total)      gives size of track or something
//


#include <SoftwareSerial.h>
#include "Adafruit_Soundboard.h"

// choose any two pins on Arduino to use for serial communication.
#define SFX_TX 5
#define SFX_RX 6

// connect to the RST pin on the soundboard for any resetting purposes on sound board.
#define SFX_RST 4

// create instance of software serial.
SoftwareSerial ss = SoftwareSerial(SFX_TX,SFX_RX);

// pass serial to Adafruit soundboard.
Adafruit_Soundboard soundboard = Adafruit_Soundboard(&ss,NULL,SFX_RST);

void setup() {
  Serial.begin(115200);
  ss.begin(9600);

  if (!soundboard.reset()) {
    Serial.println("Sound board not found");
    while (1);
  }
  Serial.println("Sound board found");

}

void loop() {
  
  soundboard.playTrack(1);
  delay(2000);

}
