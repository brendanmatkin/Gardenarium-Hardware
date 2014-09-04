// By Brendan Matkin http://brendanmatkin.info 
// brendan@brendanmatkin.info 
// MIT License
// created for http://beakerhead.org 

#include <Servo.h>

#define rangePin A0          // [D10 on attiny84a] - rangefinder (analog) 
#define timePin A1           // [D9 on attiny84a] - pot to popTime 
#define redPin A3
#define greenPin A4
#define bluePin A5
#define adjustButtonPin 8    // hold this button to modify popping time
#define relayPin 2           // fire the poppper
#define doorPin 1            // reed switch on door ?? 

#define hopperPin 9          // popcorn hopper
#define candyServoPin 10 
#define candyConveyorPin 11
#define candyTriggerPin 12

int clockPin = 5;
int latchPin = 6;
int dataPin = 7;

#define rangeMin 10          // how far away in order to start popping
#define rangeMax 80
#define hopperOpen 93        // servo setting for open hopper
#define hopperClosed 105     // servo setting for closed hopper
#define trigger 1000         // number of count to trigger execute
#define candyStop 90
#define candyVend 95

long popTime = 360000;         // 4.5 minutes in ms. = 270 000, 3 min = 180 000 
long time = popTime;         // for 7 seg display
long measure = 1000;          // tie to a pot! (how much popcorn to vend)

// numbers for 7 seg
byte numbers[] = {
  B10000001, B11001111, B10010010, B10000110, B11001100, 
  B10100100, B10100000, B10001111, B10000000, B10001100
};

Servo hopperServo;
Servo candyServo;
const float lerp = 0.20;     // 0 < lerp < 1 -- value of 1 results in no averaging.

float rangeAvg;              // averaged distance from sensor in cm. 
int count = 0;               // counter for 'in range' time
unsigned long timer = 0;     // delay timer. ALWAYS MAKE THIS LONG! How many times do I need to troubleshoot a timer rolling over because I defined it as an int? 
unsigned long cTimer = 0;    // candy timer
boolean exe = false;         // execute popcorn delivery?
boolean vendCandy = false;
boolean debug = false;        // print debug to serial

unsigned long lightTimer; 
long lightInterval = 1000;


//*********************/

void setup() {
  hopperServo.attach(hopperPin);        // initialize hopper servo
  hopperServo.write(hopperClosed);
  if (debug) Serial.begin(9600);

  //hopperServo.write(hopperClosed);      // make sure it's closed
  candyServo.attach(candyServoPin);
  candyServo.write(candyStop);

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  pinMode(doorPin, INPUT_PULLUP);
  pinMode(candyConveyorPin, OUTPUT);
  digitalWrite(candyConveyorPin, LOW);
  pinMode(candyTriggerPin, INPUT_PULLUP);
  pinMode(adjustButtonPin, INPUT_PULLUP);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  digitalWrite(redPin, HIGH);
  digitalWrite(bluePin, HIGH);
  digitalWrite(greenPin, HIGH);

  hopperServo.attach(hopperPin);        // initialize hopper servo
  hopperServo.write(hopperClosed);
}




//**********************/

void loop() {
  if (digitalRead(doorPin) == HIGH && digitalRead(adjustButtonPin) == HIGH && !exe) {    // popcorn machine door is open
    // door open code goes here
    printOff();
  }
  else {                                                      // popcorn machine door is closed
    // door closed code goes here
    rangeAvg = rangeFinder(analogRead(rangePin), rangeAvg);   // function to update averaged range distance in cm
    if (debug) Serial.println(rangeAvg);

    if (rangeAvg > rangeMin && rangeAvg < (rangeMax-1)) {
      count++;             // use a counter to filter anomalies... 
      if(!exe && digitalRead(adjustButtonPin) == HIGH) printReady();
    }
    else if (!exe) count = 0;                                 // if out of range NOT during popcorn delivery, reset the range timer

    if (count == trigger) exe = true;                         // your patience has paid off; execute popcorn delivery!
    //else hopperServo.write(hopperClosed);                   // otherwise make sure the hopper stays shut. Just in case. 
  }


  // always code also goes here
  if (exe) {
    popTheCorn();                      // run the execute function until exe is disabled (even if the door is open)
    //printTime(popTime-millis()%popTime, false);
    printTime(popTime-(millis()-timer));
  }
  else {
    if (digitalRead(adjustButtonPin) == LOW) {
      long _popTime = map(analogRead(timePin),0,1023,5000,540000);
      float _lerp = 0.025;
      popTime = _lerp*_popTime + (1.0-_lerp)*popTime;
      printTime(popTime);
    }
    //else printReady();
    else printClear();
  }

  if (digitalRead(candyTriggerPin) == LOW) {
    vendCandy = true;
    cTimer = millis();
  }
  //else vendCandy = false;
  if (vendCandy) candy();
  
  blinken();

  //delay(50);
}





//*************************/

void popTheCorn() {                                // execute function releases and cooks popcorn (non-blocking).
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







