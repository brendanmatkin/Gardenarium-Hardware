float rangeFinder (float input, float avg) {
  float volts = input*5/1024; // get actual voltage reading
  //distance = 61.681*pow(volts,-1.133); //A02 (long range: 20-150 cm)
  float distance = 27.003*pow(volts,-1.1001); //A21 (short range: 10-80 cm)
  if (distance > 80) distance = 80;
  if (distance < 10) distance = 10;
  float _avg = lerp*distance + (1.0-lerp)*avg;
  return _avg;
}
