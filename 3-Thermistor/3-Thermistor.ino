#include <math.h>
#define ThermistorPIN 0

void setup() {

  Serial.begin(9600);
  while(!Serial);
}

void loop() {
  int analogValue = analogRead(ThermistorPIN);
  Serial.print("RAW value: ");
  Serial.println(analogValue);
  double temp = Thermistor(analogValue);
  Serial.print("Temperature: ");
  printDouble(temp, 3);
  Serial.println();
  delay(2000); 
}

double Thermistor(int RawADC) {

  long Resistance;  
  double Temp;

  Resistance = 10000.0*((1024.0 / RawADC) - 1);
  Temp = log(Resistance);
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
  Temp = Temp - 273.15;
  return Temp;
}

// Thanks to mem (http://forum.arduino.cc/index.php?topic=44216.0)
void printDouble( double val, byte precision){

 Serial.print (int(val));
 
 if( precision > 0) {
  
    Serial.print(".");
    
    unsigned long frac;
    unsigned long mult = 1;
    byte padding = precision -1;
    while(precision--) mult *= 10;
    
    if(val >= 0) frac = (val - int(val)) * mult;
    else frac = (int(val)- val ) * mult;
    
    unsigned long frac1 = frac;
    while(frac1 /= 10) padding--;
    while( padding--) Serial.print("0");
    Serial.print(frac, DEC);
  }
}


