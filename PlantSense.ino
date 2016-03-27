//
// PlantSense - This sketch senses capacitive coupling between human and conductive plant
//              and then uses relative proximity to plant to control volume output through
//		MIDI.  
//

#include <CapacitiveSensor.h>
#include <midi_Message.h>
#include <MIDI.h>
#include <midi_Settings.h>
#include <midi_Defs.h>
#include <midi_Namespace.h>

// Define constants
int sendPin = 11;
int sensePin = 10;
int midiRead = 11;
double threshold = 1000;

int pitch = 0;		// set pitch. 42
int max_value = 2000;   // maximum expected sensor value. 
int velocity = 10;   // initialize volume control. Must be in mod(127). 

MIDI_CREATE_DEFAULT_INSTANCE();

CapacitiveSensor plant(sendPin, sensePin);  // _ resistor with no capacitor in parallel. 

void setup() {
  MIDI.begin(midiRead);                  // midi channel..don't need it but just include it.
  Serial.begin(115200);                  // match usb to midi baudrate
  plant.set_CS_AutocaL_Millis(10);       // set the calibration wait period in ms.
                                         // - makes the signal very stable but less sensitive.

}

void loop() {
 long sensorValue = plant.capacitiveSensor(80);
 //plant.reset_CS_AutoCal(); // force calibration

 // for debugging purposes: do not output normally or you will fuck 
 // up the midi message. 
 Serial.println(sensorValue);
 
 /* for alternate operation.
 pitch = 127*sensorValue/max_value;
 if (sensorValue > threshold) {
  MIDI.sendNoteOn(pitch,velocity,1);
  delay(1000);
  MIDI.sendNoteOff(pitch,0,1);
 }/*
 

// for modulating volume with sensor value
/* maybe wrap in if(sensorValue > threshold) statement.
velocity = 127*sensorValue/max_value;
//Serial.println(velocity);
MIDI.sendNoteOn(pitch,velocity,1);
delay(1000);
MIDI.sendNoteOff(pitch,0,1);*/


 //delay(10); // limit data to serial to avoid overload. 

}
