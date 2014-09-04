#include <Servo.h>

#define rangePin A1
#define beltPin 2
#define doorPin 9
#define doorOpen 93
int doorClosed = 107;
#define rangeMax 50
#define rangeMin 11
#define trigger 100 // number of count to trigger execute

Servo doorServo;

float range;
float distance;
float avg = 0;
float lerp = 0.20; // 0 < lerp < 1 -- value of 1 results in no averaging.
int count = 0;
int timer;
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
  range = analogRead(rangePin);
  range = range*5/1024; // get actual voltage reading
  //distance = 61.681*pow(range,-1.133); //A02 (long range: 20-150 cm)
  distance = 27.003*pow(range,-1.1001); //A21 (short range: 10-80 cm)
  if (distance > 80) distance = 80;
  if (distance < 10) distance = 10;
  avg = lerp*distance + (1.0-lerp)*avg;
  Serial.println(avg);
  Serial.println(count);
  
  if (avg < rangeMax && avg > rangeMin) count++;
  else if (!exe) count = 0;
  
  if (count >= trigger) exe = true;
  else doorServo.write(doorClosed);
  
  if (exe) execute();
  
  delay(15);
}

void execute() {
  if (count > trigger - 5 && count <= trigger + 5) {
    timer = millis();
    digitalWrite(13, HIGH);
    digitalWrite(beltPin, HIGH);
    doorServo.write(doorOpen);
  }
  if (millis() - timer >= 3000){
    //delay(3000);
    digitalWrite(beltPin,LOW);   
    digitalWrite(13,LOW);
    count = 0;
    timer = millis();
    exe = false;
  }
  else if (millis() - timer >= 500){
    //delay(500);
    doorServo.write(doorClosed);
  }
  else if (millis()-timer == 350){
    //delay(350);
    doorServo.write(doorClosed-6);
  }
}






