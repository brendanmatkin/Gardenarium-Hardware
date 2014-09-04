#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h> // do I need this??

#define deadZone 10
#define xPin 8
#define yPin 9

int zeroX;
int zeroY;
float xM,yM;
int xJ,yJ;
int dead = 35;         // dead zone range
boolean mouse = false;  // computer recognize as mouse, set false for joystick

// Accelerometer initialize
Adafruit_MMA8451 steer = Adafruit_MMA8451();
float lerpA = 0.1;


void setup()
{  
  // Initialize the serial port
  Serial.begin(115200);

  // Initialize the Nunchuk.
  steer.begin();
  steer.read();
  //zeroX = calibrate(chuck.readRoll());
  //zeroY = calibrate(chuck.readPitch());  
  
  // FINE TUNE CALIBRATE!! Maybe Calibrate Button?? 
  delay(500);
  zeroX = roll();
  zeroY = pitch();

  Joystick.useManualSend(true);
}

void loop()
{
  steer.read();
  int _xM = roll()-zeroX;
  int _yM = pitch()-zeroY;
  Serial.println(_xM);
  xM = lerpA*_xM + (1.0-lerpA)*xM;
  yM = lerpA*_yM + (1.0-lerpA)*yM;
  Serial.println(lerpA);
  Serial.println(xM);
  Serial.println();
  /*if (x < zeroX - dead || x > zeroX + dead) xM = x;
  else xM = 0;
  if (y < zeroY - dead || y > zeroY + dead) yM = y;
  else yM = 0;*/
  Mouse.move(xM/2,yM);
  //Serial.println(zeroX);

  xJ = analogRead(xPin);
  yJ = analogRead(yPin);
  Joystick.X(1023-xJ);
  Joystick.Y(1023-yJ);
  //Joystick.send_now();

  // Wait a short while
  delay(25);
}

int calibrate(int pin) {
  int num = 20;
  int value = 0;
  //int steps[num];
  for (int i = 0; i < num; i++) {
    //steps[i] = analogRead(pin);
    value += analogRead(pin);
    delay(50);
  } 
  return value/num; 
}

int roll() {
  int x = steer.x;
  int z = steer.z;
  return atan2(x,z)*180/M_PI;
}

int pitch() {
  int y = steer.y;
  int z = steer.z;
  return atan2(y,z)*180/M_PI;
}
  

