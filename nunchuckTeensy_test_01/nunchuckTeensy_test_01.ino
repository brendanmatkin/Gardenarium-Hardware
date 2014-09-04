#include <Wire.h>
#include <Nunchuk.h> // https://github.com/hughpyle/machinesalem-arduino-libs/tree/master/nunchuk


// Nunchuck for input
Nunchuk chuck = Nunchuk();


void setup()
{  
  // Initialize the serial port
  Serial.begin(115200);
  
  // Initialize the Nunchuk.
  chuck.begin();
}

void loop()
{
  // Read the current state
  chuck.read();
  //Serial.println(chuck.isOk()); // returns 1 if receiving data from nunchuck

  //Serial.print( chuck.getAccel(), DEC );
  /*Serial.print(chuck.readRoll());
  Serial.print( "\t" );
  //Serial.print( chuck.getAccelX(), DEC );
  Serial.print(chuck.readPitch());
  Serial.print( "\t" );
  //Serial.print( chuck.getAccelY(), DEC );
  Serial.print( "\t" );
  //Serial.print( chuck.getAccelZ(), DEC );
  Serial.print("z: ");
  Serial.print(chuck.getButtonZ());
  Serial.print("  +c: ");
  Serial.print(chuck.getButtonC());
  Serial.print( "\n" );*/
  
  
  // Wait a short while
  delay(50);
}


