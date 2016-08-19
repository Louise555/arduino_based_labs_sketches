// Dr. V. Lankar This program gives the magnitude of the magnetic field in Gauss
/*  using the hall effect sensor to measure the magnetic field. The stength is proportional to the voltage from A0
 voltage can only varies from 2.5V to 5V at a  rate of  2.5mv / Gauss for the A1301/A1302  - so no field= voltage is 2.5V
 For the connections see here :http://www.learningaboutelectronics.com/Articles/Hall-effect-sensor-circuit.php
  1 pin to Vcc(5V),  one pin to Gnd. 1 pin to  (A0) when you are facing the round face.  
 the code comes from: http://playground.arduino.cc/Code/HallEffect
 The sensor has about 20% error ?
 */ 
 //The code comes from:
/*
 *    FILE: MM01
 *  AUTHOR: Rob van den Tillaart; modified Ralph Martin
 *    DATE: 2012 06 10 
 *     ORIGINAL URL: http://playground.arduino.cc/Code/HallEffect
 *
 * PURPOSE: use an A1301 or A1302 as magnetometer   
 *
 * Pin Layout LH Package
 * =====================
 *  1     VCC 5V
 *  2     signal    connected to Analog 0    
 *  3     GND
 *
 * Pin Layout UA Package
 * =====================
 *  1     VCC 5V
 *  2     GND
 *  3     signal    connected to Analog 0    
 *
 */

#define NOFIELD 510L    // Analog output with no applied field, calibrate this . Read the magnetic field when no magnet is around
// and the value you will read is used for calibration. See website. 



#define TOGAUSS 1.953125 // For A1301: 2.5mV = 1Gauss, and 1024 analog steps = 5V, so 1 step = 1953mG
int sensorPin=A0; // pin connected to pin out
int j;
void setup() 
{
  Serial.begin(9600);  // make sure to change the speed with the serial monitor
  j=0;
  Serial.println("if value negative then North pole");
}

void print_data(int x, float y)
{
    Serial.print(x, DEC); 
    Serial.print(",");
    Serial.print(y, DEC);    
    Serial.println();
}

void loop() 
{
  float gauss = (analogRead(sensorPin) - NOFIELD) * TOGAUSS;
 // Serial.println(5*analogRead(sensorPin)/1024.); to write the voltage of the data pin
  print_data( j, gauss);
  
  j++;

 // if (gauss > 0)     Serial.println("(South pole)");
// else if(gauss < 0) Serial.println("(North pole)");
 // else               Serial.println();

    delay(1000);
    
}
