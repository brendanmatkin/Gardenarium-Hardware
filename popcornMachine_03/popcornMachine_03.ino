// By Brendan Matkin http://brendanmatkin.info 
// brendan@brendanmatkin.info 
// MIT License

#include <Servo.h>

#define rangePin A1          // rangefinder (analog)
#define beltPin 2            // conveyor belt
#define doorPin 9            // popcorn hopper door
#define doorOpen 93          // servo setting for open door
#define doorClosed 107       // servo setting for closed door
#define rangeMax 50          // maximum range of sensor activation window 
#define rangeMin 11          // mimimum range of sensor activation window
#define trigger 100          // number of count to trigger execute

Servo doorServo;
const float lerp = 0.20;     // 0 < lerp < 1 -- value of 1 results in no averaging.

float rangeAvg = 0;          // averaged distance from sensor in cm. 
int count = 0;               // counter for 'in range' time
unsigned long timer = 0;     // delay timer. ALWAYS MAKE THIS LONG! How many times do I need to troubleshoot a timer rolling over because I defined it as an int? 
boolean exe = false;         // execute popcorn delivery? 
boolean debug = true;        // print debug to serial (runs a leetle beet slower)


void setup() {
  if (debug) Serial.begin(19200);  // serial debug
  doorServo.attach(doorPin);       // initialize hopper door servo
  doorServo.write(doorClosed);     // make sure it's closed
  pinMode(beltPin, OUTPUT);        // conveyor belt 
  pinMode(13, OUTPUT);             // onboard LED
  digitalWrite(13,LOW);            // start with LED off... 
}


void loop() {
  rangeAvg = rangeFinder(analogRead(rangePin), rangeAvg);   // function to update averaged range distance in cm
  if (debug) Serial.println(rangeAvg);                      // debug
  
  if (rangeAvg < rangeMax && rangeAvg > rangeMin) count++;  // someone is in range! Increase the range 'timer'..
  else if (!exe) count = 0;                                 // if out of range NOT during popcorn delivery, reset the range timer
  if (debug) Serial.println(count);                         // debug
  
  if (count >= trigger) exe = true;  // your patience has paid off; execute popcorn delivery!
  else doorServo.write(doorClosed);  // otherwise make sure the hopper door stays shut. Just in case. 
  
  if (exe) execute();                // run the execute function until exe is disabled
  if (debug) delay(15);              // debug
}


void execute() {
  if (count >= trigger && count < trigger + ) {  // +5 so we don't miss it:
    timer = millis();                             // must catch count to initiate timer
    digitalWrite(13, HIGH);                       // indicator LED
    digitalWrite(beltPin, HIGH);                  // start the conveyor
    doorServo.write(doorOpen);                    // open the door
  }
  if (millis() - timer >= 3000){       // THIRD - 3 seconds later, consider increasing to 3850?
    //delay(3000);
    digitalWrite(beltPin,LOW);         // stop the conveyor
    digitalWrite(13,LOW);              // turn off indicator LED
    count = 0;                         // reset in-range counter
    timer = millis();                  // reset delay timer
    exe = false;                       // disable execute()
  }
  else if (millis() - timer >= 850){   // SECOND - 500 millis later (500+350)
    //delay(500);
    doorServo.write(doorClosed);       // close hopper door the rest of the way
  }
  else if (millis()-timer >= 350){     // FIRST - after 350 millis
    //delay(350);
    doorServo.write(doorClosed-6);     // close hopper door mostly to allow kernels to clear the gap
  }
}






