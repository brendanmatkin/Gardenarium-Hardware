#include <Wire.h>
#include <Nunchuk.h> // https://github.com/hughpyle/machinesalem-arduino-libs/tree/master/nunchuk
#define deadZone 10
#define xPin 8
#define yPin 9

int zeroX;
int zeroY;
int xM,yM;
int xJ,yJ;
int dead = 35;         // dead zone range
boolean mouse = false;  // computer recognize as mouse, set false for joystick

// Nunchuck for input
Nunchuk chuck = Nunchuk();


void setup()
{  
  // Initialize the serial port
  Serial.begin(115200);

  // Initialize the Nunchuk.
  chuck.begin();
  chuck.read();
  delay(1000);
  chuck.read();
  //zeroX = calibrate(chuck.readRoll());
  //zeroY = calibrate(chuck.readPitch());  
  zeroX = chuck.readRoll();
  zeroY = chuck.readPitch();

  Joystick.useManualSend(true);
}

void loop()
{
  chuck.read();
  xJ = analogRead(xPin);
  yJ = analogRead(yPin);


  int x = chuck.readRoll()-zeroX;
  int y = chuck.readPitch()-zeroY;
  /*if (x < zeroX - dead || x > zeroX + dead) xM = x;
  else xM = 0;
  if (y < zeroY - dead || y > zeroY + dead) yM = y;
  else yM = 0;*/
  Mouse.move(-x/2,y);
  //Serial.println(zeroX);
  //Serial.println(chuck.readRoll()-zeroX);
  //Serial.println(chuck.readRoll());
  Joystick.X(1023-xJ);
  Joystick.Y(1023-yJ);
  Joystick.send_now();


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

