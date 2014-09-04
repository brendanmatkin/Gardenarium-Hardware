import oscP5.*;
import netP5.*;
import processing.serial.*;

Serial myPort;
OscP5 oscP5; 
NetAddress myRemoteLocation;
int listen = 9001;
long timer = 0;

void setup() {
  size(500,50);
  oscP5 = new OscP5(this, listen);
  myRemoteLocation = new NetAddress("127.0.0.1", 9000);
  oscP5.plug(this, "vend", "/vend");
  
  myPort = new Serial(this, Serial.list()[1], 9600);
  
  
}

void draw() {
  background(255);
  String display = "OSC to serial listening on port: " + listen;
  fill(50);
  textSize(16);
  text(display,10,15);
  if (millis()-timer <= 1000) text("VEND!", 10,30);
}

void vend(int _vend) {
  println(_vend);
  myPort.write(_vend);
  timer = millis();
}
