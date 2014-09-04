#define deadZone 10
#define xPin 8
#define yPin 9

int zeroX;
int zeroY;
int x,y;
int dead = 35;         // dead zone range
int spd = 5;          // mouse speed
boolean mouse = false;  // computer recognize as mouse, set false for joystick

void setup() { 
  Serial.begin(9600);
  if (mouse) {
    zeroX = calibrate(xPin);
    zeroY = calibrate(yPin);  
  }
  else Joystick.useManualSend(true);
}

void loop() {
  x = analogRead(xPin);
  y = analogRead(yPin);

  if (mouse){
    if (x < zeroX - dead || x > zeroX + dead) x = map(x,0,1023,spd,-spd);
    else x = 0;
    if (y < zeroY - dead || y > zeroY + dead) y = map(y,0,1023,spd,-spd);
    else y = 0;
    Mouse.move(x,y);
    delay(25);
  }
  else {
    Joystick.X(1023-x);
    Joystick.Y(1023-y);
    Joystick.send_now();
    delay(5);
  }
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


