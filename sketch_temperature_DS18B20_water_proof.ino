//Dr.  V. Lankar 6/16/16 - Physics dept.
// using  WATERPROOF DS18B20 thermometer adafruit - Usable temperature range: -55 to 125°C (-67°F to +257°F)
//Unique 64 bit ID burned into chip - ±0.5°C Accuracy from -10°C to +85°C - can be used with 3.3V as well
// Red connects to 5V, Blue/Black connects to ground and Yellow/White is data (pin 10)
// and you need a 4.7K resistor between data wire (pin 10) and 5V - This is a pull-up resistor. So when there is no data collected
// the data is 5V.  
//https://www.adafruit.com/products/381
//
// I found the code here:  http://garagelab.com/profiles/blogs/tutorial-waterproof-temperature-sensor-ds18b20-with-arduino
// but there is a typo MSB <<8   instead of MSB 8 
// you need to dowload the library below. see website above to dowload the libray as a .zip file
//
// the data are sent to the serial monitor with a .csv format: time in ms,temperature in celsius
// example : 3,22.5
// So you can copy the data in a spreadsheet in a csv format
//
#include <OneWire.h> // library to communicate with the sensor. 1 wire interface. to be downloaded. 

int SensorPin = 10; 

OneWire ds(SensorPin); // telling the library which pin is connected to the data wire

void setup(void) {
Serial.begin(9600); // to be able to display in the monitor
}
// just a function to write the data on the serial monitor. time(ms) and temp9C) 
void print_data(unsigned long x, float y)
{
    Serial.print(x, DEC); 
    Serial.print(",");
    Serial.print(y, DEC);    
    Serial.println();
}

void loop(void) {
float temp = getTemp();
  print_data(millis(),temp); // display in the serial monitor time in ms and temperature in C
  delay(1000); // wait for 1 second before reading the next temperature
}


float getTemp(){

byte data[12];
byte addr[8];

if ( !ds.search(addr)) {
//no more sensors on chain, reset search
ds.reset_search();
return -1000;
}

if ( OneWire::crc8( addr, 7) != addr[7]) {
Serial.println("CRC is not valid!");
return -1000;
}

if ( addr[0] != 0x10 && addr[0] != 0x28) {
Serial.print("Device is not recognized");
return -1000;
}

ds.reset();
ds.select(addr);
ds.write(0x44,1); 

byte present = ds.reset();
ds.select(addr); 
ds.write(0xBE); 


for (int i = 0; i < 9; i++) { 
data[i] = ds.read();
}

ds.reset_search();

byte MSB = data[1];
byte LSB = data[0];
float TRead = ((MSB <<8) | LSB ); 
float Temperature = TRead / 16;

return Temperature;

}
