// (Dr. V.Lankar 2016) - charge and discharge of a capacitor. The output is time(ms) voltage(V)
// When reading in a spreadsheet the format is .csv/ The baud rate is 115200 to select in Serial monitor. 
// the expected time constant is 1000uF x 4.5 K = 4.5 seconds - Use a multimeter to measure the resistance of the resistor.
// the capacitor is charging and discharging in the resistor. 
/* circuit: output pin 7 - resistor 4.5K  - input A0 - capacitor 
/* 1000 micro - Grnd
 * original code by: 
 * Yves Pelletier
 *
 * http://electroniqueamateur.blogspot.com
 *
 ***************************************************************/
 // we read the tension across the capacitor. The tension is between 0 and 1023 (that is between 0 and 5V)
 // Then the tension is converted to volts by dividing by 1023 and by multiplying by 5V.
 // We need to find the maximum tension during charge by running trials. Here it seems to be 1010 which is 4.9V

int etat = 0;  // 0 at beginining , 1 during chargge
               // 2 discharge , 3 when it is done. 
long previousMillis = 0; 
long interval = 50;  // time between 2 measures
boolean flag=1; // just for the beginning


void setup() {   

  pinMode(7, OUTPUT);  // pin for the capacitor
  Serial.begin(115200);  // when you open the monitor make sure to select the right number of bauds.

// first we need to make sure the capacitor is totally discharged
// we wait for 5 s
  digitalWrite(7,LOW);
  delay(5000);

  // new state - charge
  etat = 1;
//  charging capacitor 5V
  digitalWrite(7,HIGH); 

}
// this is just a function to format the data on the screen
void print_data(unsigned long x, float y)
{
    Serial.print(x, DEC); 
    Serial.print(",");
    Serial.print(y, DEC);    
    Serial.println();
}
void loop() {

  unsigned long currentMillis = millis();
  int tension;
  // ready to take a new measurement
  if(currentMillis - previousMillis >= interval || flag==1) {
    
    flag=0;
    previousMillis = currentMillis; // keep track of time. 

    if (etat == 1) {  // charge of capacitor 
      tension = analogRead(A0);
      if (tension < 1010){  // not completely charged - this has to be changed if another resistor used. 
        // print_data(millis(), tension);  
       print_data(millis(), 5.*tension/1023.);        
      }
      else{  // completement chargé
        // change state discharge
        etat = 2;
        
    //    Serial.println("Decharge du condensateur");
        digitalWrite(7,LOW);  // the pin 7 goes to 0 the capacitor is discharging. 
      }
    }

    if (etat == 2) {  // discharge
      tension = analogRead(A0);
      if ( tension > 50){ // not fully discharged
        // print_data(millis(), tension);  
      print_data(millis(), 5.*tension/1023.);
      }
      else {  // discharged 
        etat = 3;  // we change state we are done
        while(1);
      }

    }
  }


}

