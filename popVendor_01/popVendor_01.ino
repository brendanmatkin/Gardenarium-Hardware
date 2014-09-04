#include <Servo.h>
#define vendClosed 180
#define vendOpen 75

Servo vendorServo;

int servoPin = 3;
int val = vendClosed;
int prevVal = vendClosed;
int vendSpeed = 3;     // lower is faster!
boolean vend = false;  // auto vend


//****************************
void setup() {
  vendorServo.attach(servoPin);
  Serial.begin(9600);
  //vendorServo.write(val);
  vendorServo.write(vendClosed);
}


//***************************
void loop() {
  if(Serial.available()>0) {
    //val = (int)Serial.read();
    val = Serial.parseInt();
    val += Serial.parseInt();
    vend = true;
  }
  Serial.println(vend);
  if (vend) autoVend(200); // 150-200 seems best
  //serialVend();
  //Serial.println(val);
 
  delay(15);
}


//********************************************
void autoVend(int wait) {
  for (int i = vendClosed; i > vendOpen; i--) {
    vendorServo.write(i);
    delay(vendSpeed);
  }
  delay(wait);
  for (int i = vendOpen; i < vendClosed; i++) {
    vendorServo.write(i);
    delay(vendSpeed);
  }
  vend = false;
}


//***************************
void serialVend() {
  if (val > prevVal) {
    for (int i = prevVal; i < val; i++) {
      vendorServo.write(i);
      delay(vendSpeed);
    }
    prevVal = val;
  }
  else {
    for (int i = prevVal; i > val; i--) {
      vendorServo.write(i);
      delay(vendSpeed);
    }
    prevVal = val;
  }
}

