#include <math.h>
#define ThermistorPIN 0

int nixieDecsPins[4] = {5,4,3,2};
int nixieUnitsPins[4] = {9,8,7,6};
byte bcd[10][4] = {
  {0,0,0,0},  // 0
  {0,0,0,1},  // 1
  {0,0,1,0},  // 2
  {0,0,1,1},  // 3
  {0,1,0,0},  // 4
  {0,1,0,1},  // 5
  {0,1,1,0},  // 6 
  {0,1,1,1},  // 7
  {1,0,0,0},  // 8
  {1,0,0,1},  // 9
};

void setup() {

  // set all the Nixie PINs as output
  for(int i = 0; i < 4; i++) {
    pinMode(nixieDecsPins[i], OUTPUT);
    pinMode(nixieUnitsPins[i], OUTPUT);
  }
}

void loop() {

  // read the value from the analog pin the thermistor is connected to
  int analogValue = analogRead(ThermistorPIN);

  // convert to temperature using the Steinhart-Hart equation
  // we only need the integer part
  int temperature = int(Thermistor(analogValue));

  // display the decimal value on the DecsNixie
  outputToNixie(temperature / 10, nixieDecsPins);
  
  // display the unit value on the UnitsNixie
  outputToNixie(temperature % 10, nixieUnitsPins);

  delay(2000);
}


void outputToNixie(int value, int nixiePins[]) {

  for(int i = 0; i < 4; i++)
    digitalWrite(nixiePins[i], bcd[value][i]);
}


// Reference: http://playground.arduino.cc/ComponentLib/Thermistor2
double Thermistor(int RawADC) {

  long Resistance;  
  double Temp;

  Resistance = 10000.0*((1024.0 / RawADC) - 1);
  Temp = log(Resistance);
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
  Temp = Temp - 273.15;
  return Temp;
}

