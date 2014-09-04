int latchPin = 9;
int clockPin = 8;
int dataPin = 10;

int refresh = 0; // delay of refresh in milliseconds
long timer = 30000; // 3 minutes = 180000
long time = timer;

byte numbers[] = {
  B10000001, B11001111, B10010010, B10000110, B11001100, 
  B10100100, B10100000, B10001111, B10000000, B10001100
};

//byte pins = B11111111;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  //Serial.begin(9600);
}

void loop() {
  printTime();
  //printReady();

}

void printReady() {
  byte _r = B11111010;
  byte _e = B10110000;
  byte _a = B10001000;
  byte _h = B11101000;
  byte _y = B11000100;
  
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, B11101111);
  shiftOut(dataPin, clockPin, LSBFIRST, _y);
  digitalWrite(latchPin, HIGH);
  
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, B11011111);
  shiftOut(dataPin, clockPin, LSBFIRST, _e);
  digitalWrite(latchPin, HIGH);
  
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, B10111111);
  shiftOut(dataPin, clockPin, LSBFIRST, _h);
  digitalWrite(latchPin, HIGH);
}

void printTime() {
  time = timer-millis()%timer;
  int d1 = time/60000 % 60;
  int _d2 = (time/1000 %60);
  int d2 = (_d2/10)%10;
  int d3 = _d2%10;

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, B10111111);
  shiftOut(dataPin, clockPin, LSBFIRST, numbers[d1]);
  digitalWrite(latchPin, HIGH);
  //delay(refresh);

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, B11011111);
  shiftOut(dataPin, clockPin, LSBFIRST, numbers[d2]);
  digitalWrite(latchPin, HIGH);
  //delay(refresh);

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, B11101111);
  shiftOut(dataPin, clockPin, LSBFIRST, numbers[d3]);
  digitalWrite(latchPin, HIGH);
  //delay(refresh);

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, B11110111);
  shiftOut(dataPin, clockPin, LSBFIRST, B10011111);
  digitalWrite(latchPin, HIGH);
  //delay(refresh);
}





