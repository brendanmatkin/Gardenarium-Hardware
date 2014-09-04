// By Brendan Matkin http://brendanmatkin.info 
// brendan@brendanmatkin.info 
// MIT License
// created for http://beakerhead.org 

#include <Servo.h>
//#include <TinyWireM.h>                  // I2C Master lib for ATTinys which use USI - comment this out to use with standard arduinos
//#include <LiquidCrystal_I2C.h>          // for LCD w/ GPIO MODIFIED for the ATtiny
#define rangeMax 80
#define rangePin A0          // rangefinder (analog) [D10 on attiny84a]
#define levelPin A1          // pot to adjust popcorn level trigger
#define measurePin A2        // pot to adjust kernal dispense amount
#define hopperPin 5          // popcorn hopper
#define relayPin 4
#define doorPin 3 
#define hopperOpen 93        // servo setting for open hopper
#define hopperClosed 107     // servo setting for closed hopper
#define trigger 100          // number of count to trigger execute

long popTime = 3000;         // 4.5 minutes in ms. = 270 000, 3 min = 180 000 
int popcornLevel = 25;       // tie to a pot? 
long measure = 350;          // tie to a pot?

Servo hopperServo;
const float lerp = 0.20;     // 0 < lerp < 1 -- value of 1 results in no averaging.

float rangeAvg;              // averaged distance from sensor in cm. 
int count = 0;               // counter for 'in range' time
unsigned long timer = 0;     // delay timer. ALWAYS MAKE THIS LONG! How many times do I need to troubleshoot a timer rolling over because I defined it as an int? 
boolean exe = false;         // execute popcorn delivery? 
boolean debug = true;        // print debug to serial


//*********************/

void setup() {
  if (debug) Serial.begin(9600);
  hopperServo.attach(hopperPin);       // initialize hopper servo
  hopperServo.write(hopperClosed);     // make sure it's closed
  pinMode(relayPin, OUTPUT);
  pinMode(doorPin, INPUT_PULLUP);
  digitalWrite(relayPin, LOW);
}


//**********************/

void loop() {

  if (digitalRead(doorPin) == HIGH) {                         // popcorn machine door is open
    // door open code goes here
    int _popcornLevel = map(analogRead(levelPin),0,1023,10,80);
    if (_popcornLevel != popcornLevel) {
      // code to run when popcorn level is changed!
      popcornLevel = _popcornLevel;
      Serial.print("popcorn level: ");
      Serial.println(popcornLevel);
    }
    /*int _measure = map(analogRead(measurePin),0,1023,50,650);
     if (_measure != measure) {
     // code to run when popcorn level is changed!
     measure = _measure;
     Serial.print("measure time: ");
     Serial.println(measure);
     }*/
  }
  else {                                                      // popcorn machine door is closed
    // door closed code goes here
    rangeAvg = rangeFinder(analogRead(rangePin), rangeAvg);   // function to update averaged range distance in cm
    if (debug) Serial.println(rangeAvg);

    if (rangeAvg > popcornLevel && rangeAvg < (rangeMax-1)) count++;                     // use a counter to filter anomalies... 
    else if (!exe) count = 0;                                 // if out of range NOT during popcorn delivery, reset the range timer

    if (count == trigger) exe = true;                         // your patience has paid off; execute popcorn delivery!
    //else hopperServo.write(hopperClosed);                     // otherwise make sure the hopper stays shut. Just in case. 
  }


  // always code also goes here
  if (exe) execute();                      // run the execute function until exe is disabled (even if the door is open)
  delay(50);
}



//*************************/

void execute() {                                // execute function releases and cooks popcorn (non-blocking).
  if (count == trigger) {
    timer = millis();                           // must catch count to initiate timer
    hopperServo.write(hopperOpen);              // open the hopper
    if (debug) Serial.println("hopper open");
    digitalWrite(relayPin, HIGH);
    if (debug) Serial.println("popper ON");
  }

  if (millis() - timer >= popTime){             // THIRD - 3 seconds later, consider increasing to 3850?
    digitalWrite(relayPin, LOW);
    if (debug) Serial.println("popper OFF");
    count = 0;                                  // reset in-range counter
    timer = millis();                           // reset delay timer
    exe = false;                                // disable execute()
  }
  else if (millis() - timer >= measure+500){            // SECOND - 500 millis later (500+350)
    hopperServo.write(hopperClosed);            // close hopper the rest of the way
    if (debug) Serial.println("hopper closed");
  }
  else if (millis() - timer >= measure){            // FIRST - after 350 millis
    hopperServo.write(hopperClosed-6);          // close hopper mostly to allow kernels to clear the gap
    if (debug) Serial.println("hopper closing");
  }
}



