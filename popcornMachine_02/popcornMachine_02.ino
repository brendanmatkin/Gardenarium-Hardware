#include <Servo.h>

#define rangePin A1          // rangefinder (analog)
#define beltPin 2            // conveyor belt
#define doorPin 9            // hopper door
#define doorOpen 93          // servo setting for open door
#define doorClosed 107       // servo setting for closed door
#define rangeMax 50          // maximum range of sensor activation window 
#define rangeMin 11          // mimimum range of sensor activation window
#define trigger 100          // number of count to trigger execute

Servo doorServo;
const float lerp = 0.20;     // 0 < lerp < 1 -- value of 1 results in no averaging.

float rangeAvg = 0;          // 
int count = 0;
int timer = 0;
boolean exe = false;

void setup() {
  Serial.begin(19200);
  doorServo.attach(doorPin);
  doorServo.write(doorClosed);
  pinMode(beltPin, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13,LOW);
}

void loop() {
  rangeAvg = rangeFinder(analogRead(rangePin), rangeAvg);
  //range = analogRead(rangePin); 
  Serial.println(rangeAvg);
  
  if (rangeAvg < rangeMax && rangeAvg > rangeMin) count++;
  else if (!exe) count = 0;
  Serial.println(count);
  
  if (count >= trigger) exe = true;
  else doorServo.write(doorClosed);
  
  if (exe) execute();
  
  delay(15);
}



void execute() {
  if (count >= trigger && count < trigger + 5) {  // +5 so we don't miss it:
    timer = millis();                             // must catch count to initiate timer
    digitalWrite(13, HIGH);                       // indicator LED
    digitalWrite(beltPin, HIGH);                  // start the conveyor
    doorServo.write(doorOpen);                    // open the door
  }
  if (millis() - timer >= 3000){ // 3850?
    //delay(3000);
    digitalWrite(beltPin,LOW);   
    digitalWrite(13,LOW);
    count = 0;
    timer = millis();
    exe = false;
  }
  else if (millis() - timer >= 850){
    //delay(500);
    doorServo.write(doorClosed);
  }
  else if (millis()-timer >= 350){
    //delay(350);
    doorServo.write(doorClosed-6);
  }
}






