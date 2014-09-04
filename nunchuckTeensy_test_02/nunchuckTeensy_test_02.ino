#include <Wire.h>
#include <Nunchuk.h> // https://github.com/hughpyle/machinesalem-arduino-libs/tree/master/nunchuk


// Nunchuck for input
Nunchuk chuck = Nunchuk();

int zeroX;
int zeroY;


void setup()
{  
  // Initialize the serial port
  Serial.begin(115200);
  
  // Initialize the Nunchuk.
  chuck.begin();
  chuck.read();
  
  // zero the controller 
  delay(500);
  chuck.read();
  zeroX = chuck.readRoll();
  zeroY = chuck.readPitch();
  Joystick.useManualSend(true);
}

void loop()
{
  // Read the current state
  chuck.read();
  //Serial.println(chuck.isOk()); // returns 1 if receiving data from nunchuck
  //Serial.print( chuck.getAccel(), DEC );
  /*Serial.print(chuck.readRoll());
  //Serial.print( chuck.getAccelX(), DEC );
  Serial.print(chuck.readPitch());
  //Serial.print( chuck.getAccelY(), DEC );
  //Serial.print( chuck.getAccelZ(), DEC );
  Serial.print(chuck.getButtonZ());
  Serial.print(chuck.getButtonC());*/
  //Joystick.X(chuck.readRoll()-zeroX);
  //Joystick.Y(chuck.readPitch()-zeroY);
  //Joystick.send_now();
  int x = chuck.readRoll()-zeroX;
  int y = chuck.readPitch()-zeroY;
  Mouse.move(-x/2,y*2);
  Serial.println(zeroX);
  Serial.println(chuck.readRoll()-zeroX);
  //Serial.println(chuck.readRoll());
  
  
  // Wait a short while
  delay(50);
}


