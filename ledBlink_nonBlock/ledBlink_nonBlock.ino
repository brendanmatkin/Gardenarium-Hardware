#define redPin A3
#define bluePin A4
#define greenPin A5

unsigned long lightTimer; 
long lightInterval = 1000;


void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  digitalWrite(redPin, HIGH);
  digitalWrite(bluePin, HIGH);
  digitalWrite(greenPin, HIGH);
}

void loop() {
  blinken();
}

void blinken() {
  int steps = 6;
  if (millis()%(lightInterval*steps) >= lightInterval*(steps-1)) digitalWrite(bluePin, HIGH);       // blue off
  else if (millis()%(lightInterval*steps) >= lightInterval*(steps-2)) digitalWrite(greenPin, LOW);  // green on
  else if (millis()%(lightInterval*steps) >= lightInterval*(steps-3)) digitalWrite(redPin, HIGH);   // red off
  else if (millis()%(lightInterval*steps) >= lightInterval*(steps-4)) digitalWrite(bluePin, LOW);   // blue on
  else if (millis()%(lightInterval*steps) >= lightInterval*(steps-5)) digitalWrite(greenPin, HIGH); // green off
  else if (millis()%(lightInterval*steps) >= lightInterval*(steps-6)) digitalWrite(redPin, LOW);    // red on 
}
