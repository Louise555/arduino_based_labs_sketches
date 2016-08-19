/*Dr.V. Lankar
 * experiment: computation of acceleration due to gravity. need photo transistor + laser. The phototransistor detects change of state.
 * The phototransistor breakout comes from elab peers.com. It works very well. See the sketch to test it firs.
 * I use a red laser box (used for optics) but you can also use theirs. 
 * We use a polycarbonate sheet (6in x 12in ) http://electroniqueamateur.blogspot.com/2015/04/mesure-de-lacceleration-gavitationnelle.html?m=1
 * we drop the plate between the laser and detector and compute the time between each change of state (black tape and transparance)
 * the distance covered between the states is 3.5cm. 
In this experiment we use a phototransistor that works only with digitalpin. 
the laser is independently powerd. not controled by the arduino. 
The laser has to aim at the phototransistor (see video on elabpeers for details). the code compute the time between each change of state in ms.
See here for more details. 
http://electroniqueamateur.blogspot.com/2015/04/mesure-de-lacceleration-gavitationnelle.html?m=1

you need to take only the first 7 points

time is in ms. 

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


*/
int debut=1;
int Detector = 7;
int etat_precedent=1; // previous state
int etat_actuel=1; // current state
unsigned long temps_debut; // time when the code starts to run
int j=0;



void setup()
{ 
  Serial.begin (9600);
  pinMode(Detector, INPUT);
}

void print_data(int x, long y)
{
    Serial.print(x, DEC); 
    Serial.print(",");
    Serial.print(y, DEC);    
    Serial.println();
}

void loop()
{
  etat_actuel= digitalRead(Detector); // reading 
  if (etat_actuel !=etat_precedent) {      //change of state
    if (debut) // if first time we record the time of beginning
    {
      temps_debut=millis();
      debut=0;
    }
     print_data(j,millis()-temps_debut);
     j++;
 //    Serial.println(millis()-temps_debut);
     etat_precedent=etat_actuel;
    


  }
  
  
}  
