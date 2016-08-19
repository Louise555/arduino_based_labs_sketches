/* you need: inductor (Pasco 3200 turns with core 145 ohms) and 10 ohms resistor 
 *  The inductor  is a solenoid with 3200 turns from pasco with an iron core.
the core boosts the inductor by a factor of about 3 to 4 .  The inductance is boosted from 0.2 to  0.7 H  with core. the resistance is about 145ohms. 
You need to check that with a multimeter.  https://www.pasco.com/prodGroups/coils-and-cores/index.cfm#orderItem_SF-8613
We don't want a large total resistance because time constant  =L/R so if R small then time constant is big. 
It seems that 10 ohms is the best value. Too small and the voltage across it is too small. Too large and L/R is too small. 
The set up is : digital pin 7 (5V or 0V) - inductor (145 ohms) - pin A0 - resistor 10 ohms -Gnd
the idea is to measure the voltage across the 10 ohms resistor to see how the current behaves as a function of time
we expect a exponential decay and the time constant inside the exponential is L/R. exp(-time/(L/R))  With R = 145+10 ohms. 
The time is in microseconds because the time constant is small. 0.004 second about. The voltage is between 0 and 5V. 
so we print in the serial monitor: time in microseconds and voltage across the resistor.  
We observe first the charge then the discharge. Copy and paste in a spreadsheet the charge then the discharge to plot 2 different plots. 
see for original code for capacitor that I modified http://electroniqueamateur.blogspot.com
*/

int etat; // is 1 during the charge - 2 during discharge - 3 we are done. totally discharged.
float tension;
void setup() {   

  pinMode(7, OUTPUT);  // pin 7 is used to apply a voltage of 5 during charge or 0 during discharge.
  Serial.begin(115200);  // make sure to change the baud rate.

  digitalWrite(7,LOW); // discharging before we start .
  delay(5000); // we give ouself time to click on the monitor
  // nouvel etat:  charge du condensateur
  etat = 1;
  digitalWrite(7,HIGH);  // charging the inductor. state is 1. 
}

// just a function to format the serial monitor output
void print_data(unsigned long x, float y)
{
    Serial.print(x, DEC); 
    Serial.print(",");
    Serial.print(y, DEC);    
    Serial.println();
}

void loop() {
  
    
    if (etat == 1) { // charging 
      
      tension = analogRead(A0); // reading from analog pin voltage across 10 ohms, The voltage is between 0 and 1023 . It has to be changed nxt in volts. 
      if (tension < 56){  //  56 for 10 ohms (56*5/1023 volts). if voltage is 56 then the inductor is completly charged. only true for 10 ohms in series with 145 ohms from inductor
        print_data(micros(),tension*5./1023); // writing.
      }
      else{  // charged
        // discharging now. 
        etat = 2;
        digitalWrite(7,LOW);  // pin 7 = 0V
      }
        
      }
    

    if (etat == 2) {  // décharge
      tension = analogRead(A0);
      if (tension > 0){ // not yet discharged
        print_data(micros(),tension*5./1023);
      }
      else {  // completement déchargé
        print_data(micros(),tension);
        etat=3;
      }

    }
}


