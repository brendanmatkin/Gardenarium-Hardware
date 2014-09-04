// Written by Brendan Matkin for Beakerhead Drive-In Arcade 2014
// for use with Teensy 3.1
// MIT License

#include <Wire.h>
#include <Adafruit_MMA8451.h>    // data pin 18, clk pin 19
#include <Adafruit_Sensor.h>     // do I need this??
#include <Bounce.h>
#include <Servo.h>

#define xPin 22           // joystick
#define yPin 23           // joystick
#define calibratePin 14   // zero the mouse (steering wheel)
#define resetPin 15       // reset the game "r"
#define modeSwitchPin 16  // switch to and from mini game "c"
#define hornPin 17        // horn pin for mouseClick (left click)

#define popServoPin 20  // servo for pop release
#define vendClosed 175
#define vendOpen 75
boolean vend = false;
int vendSpeed = 3;      // lower is faster!

int zeroX;              // mouse calibration
int zeroY;              // mouse calibration
float xM,yM;            // mouse x,y
int xJ,yJ;              // joystick x,y
boolean mouse = false;  // computer recognize as mouse, set false for joystick
boolean debug = true;

// Accelerometer initialize
Adafruit_MMA8451 steer = Adafruit_MMA8451();
Servo popServo;


Bounce horn = Bounce(hornPin, 10);    // de-bouncing object for the horn (mouse click)
Bounce calibrate = Bounce(calibratePin, 10);
Bounce modeSwitch = Bounce(modeSwitchPin, 10);
Bounce resetGame = Bounce(resetPin, 10);
byte leftClick = 0;


void setup()
{  
  // Initialize the serial port
  if (debug) Serial.begin(115200);
  else Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  // Initialize the accelerometer
  steer.begin();
  steer.read();
  //zeroX = calibrate(chuck.readRoll());
  //zeroY = calibrate(chuck.readPitch());  

  pinMode(hornPin, INPUT_PULLUP);
  pinMode(calibratePin, INPUT_PULLUP);
  pinMode(modeSwitchPin, INPUT_PULLUP);
  pinMode(resetPin, INPUT_PULLUP);
  popServo.attach(popServoPin);
  popServo.write(vendClosed);

  // calibrate (only works on reset on windows 8 for some reason? Manual calibrate button below. 
  delay(500);
  zeroX = roll();
  zeroY = pitch();

  Joystick.useManualSend(true);
  if(debug) Serial.println("I'm alive");
}




void loop()
{
  if (Serial.available() > 0) {
    int incoming = Serial.read();
    if (incoming > 0) vend = true;
    else vend = false; 
  }
  else vend = false; 
  // mouse movement
  steer.read();
  float _xM = (roll()-zeroX);
  float _yM = (pitch()-zeroY);
  if (debug) Serial.println(_xM);
  float lerpA = 0.05;      // averaging - 0>lerp>1 - averaging is smoother as lerp approaches 0. 
  xM = lerpA*_xM + (1.0-lerpA)*xM;
  yM = lerpA*_yM + (1.0-lerpA)*yM;
  if (debug) Serial.println(xM);
  if (debug) Serial.println();
  Mouse.move(xM,yM);

  // mouse clicks
  horn.update();
  byte clickChange = 0;
  if (horn.fallingEdge()) {     // mouse press
    leftClick = 1;
    clickChange = 1;
  }
  if (horn.risingEdge()) {    //  mouse release
    leftClick = 0;
    clickChange = 1;
  }
  if (clickChange) Mouse.set_buttons(leftClick,0,0);

  // other buttons
  calibrate.update();
  modeSwitch.update();
  resetGame.update();
  if (calibrate.fallingEdge()) {
    zeroX = roll();
    zeroY = pitch();
  }
  if (modeSwitch.fallingEdge()) Keyboard.print("c");
  if (resetGame.fallingEdge()) Keyboard.print("r");

  // joystick movements
  xJ = analogRead(xPin);
  yJ = analogRead(yPin);
  Joystick.X(xJ);
  Joystick.Y(yJ);
  Joystick.send_now();

  // pop vendor
  if (vend) autoVend(300);

  // Wait a short while
  if (debug) delay(10);
}

/*int calibrate(int pin) {
 int num = 20;
 int value = 0;
 //int steps[num];
 for (int i = 0; i < num; i++) {
 //steps[i] = analogRead(pin);
 value += analogRead(pin);
 delay(50);
 } 
 return value/num; 
 }*/

float roll() {
  float x = steer.x;
  float z = steer.z;
  return atan2(x,z)*180/M_PI;
}

float pitch() {
  float y = steer.y;
  float z = steer.z;
  return atan2(y,z)*180/M_PI;
}

//********************************************
void autoVend(int wait) {
  for (int i = vendClosed; i > vendOpen; i--) {
    popServo.write(i);
    digitalWrite(13, HIGH);
    delay(vendSpeed);
  }
  delay(wait);
  for (int i = vendOpen; i < vendClosed; i++) {
    popServo.write(i);
    digitalWrite(13, LOW);
    delay(vendSpeed);
  }
  vend = false;
}





