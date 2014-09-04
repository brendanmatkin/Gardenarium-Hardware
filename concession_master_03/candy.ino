void candy() {
  candyServo.write(candyVend);
  //digitalWrite(candyConveyorPin, HIGH);
  analogWrite(candyConveyorPin, 200);
  if (millis() - cTimer >= 1250) candyServo.write(candyStop);
  if (millis() - cTimer >= 3000) {
    vendCandy = false;
    //digitalWrite(candyConveyorPin, LOW);
    analogWrite(candyConveyorPin, 0);
  }
}

/*void stopCandy() {
  candyServo.write(candyStop);
}*/
