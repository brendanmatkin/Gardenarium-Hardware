void printTime(long inputTime) {
  time = inputTime;
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


void printReady() {
  byte _h = B11101000;
  byte _e = B10110000;
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

void printClear() {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, B11110111);
  shiftOut(dataPin, clockPin, LSBFIRST, B11111111);
  digitalWrite(latchPin, HIGH);
  
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, B11101111);
  shiftOut(dataPin, clockPin, LSBFIRST, B11111111);
  digitalWrite(latchPin, HIGH);
  
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, B11011111);
  shiftOut(dataPin, clockPin, LSBFIRST, B11111111);
  digitalWrite(latchPin, HIGH);
  
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, B10111111);
  shiftOut(dataPin, clockPin, LSBFIRST, B11111111);
  digitalWrite(latchPin, HIGH);
}
