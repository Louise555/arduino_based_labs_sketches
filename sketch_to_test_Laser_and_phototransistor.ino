/*
 * Dr. V. Lankar sketch to test the set up laser + phototransistor
 * See the website elabpeers.com . the code comes from there.
 * http://www.elabpeers.com/ky-008-laser-x-laser-detector.html
 * you can use their laser + their phototransistor but I only use the phototransistor
 * and a laser from our lab.


Code for KY-008 Laser and Laser Detector
by eLab Peers (C) 2014.

Visit us at:
http://www.elabpeers.com

All rights reserved.

Wiring:
for phototransistor:
Gnd to Gnd
Vcc to 5V 
out to pin 7
for laser

for laser KY-008 : (I don't use that) 
- to Gnd
middle to 5V
S to pin 6


*/

int Laser = 6; // only if u use their laser.
int Detector = 7;

void setup()
{ 
  Serial.begin (9600);
  pinMode(Laser, OUTPUT);
  pinMode(Detector, INPUT);
}

void loop()
{
  digitalWrite(Laser, HIGH);
  boolean val = digitalRead(Detector);
  Serial.println(val);
}  
