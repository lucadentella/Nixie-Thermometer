#include <math.h>
#include <Adafruit_NeoPixel.h>

#define THERM_PIN    0
#define BUTTON_PIN   10
#define PIXEL_PIN    16
#define PIXEL_COUNT   3

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

uint8_t colors[8][3] = {
  {0,0,0},
  {255,0,0},
  {0,255,0},
  {0,0,255},
  {255,255,0},
  {255,0,255},
  {0,255,255},
  {255,255,255},
};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

bool oldState = HIGH;
int actualColor = 0;

void setup() {

  Serial.begin(9600);
  
  // set all the Nixie PINs as output
  for(int i = 0; i < 4; i++) {
    pinMode(nixieDecsPins[i], OUTPUT);
    pinMode(nixieUnitsPins[i], OUTPUT);
  }
  
  pinMode(BUTTON_PIN, INPUT);
  strip.begin();
  showActualColor();
}

void loop() {

  // read the value from the analog pin the thermistor is connected to
  int analogValue = analogRead(THERM_PIN);

  // convert to temperature using the Steinhart-Hart equation
  // we only need the integer part
  int temperature = int(Thermistor(analogValue));

  // display the decimal value on the DecsNixie
  outputToNixie(temperature / 10, nixieDecsPins);
  
  // display the unit value on the UnitsNixie
  outputToNixie(temperature % 10, nixieUnitsPins);
  
  bool newState = digitalRead(BUTTON_PIN);
  if (newState == LOW && oldState == HIGH) {
    delay(20);
    newState = digitalRead(BUTTON_PIN);
    if (newState == LOW) {
      Serial.println("Button clicked");
      actualColor++;
      if(actualColor == 8) actualColor = 0;
      showActualColor();
    }
  }
  oldState = newState;

  delay(500);
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


void showActualColor() {

  uint8_t red = colors[actualColor][0];
  uint8_t green = colors[actualColor][1];
  uint8_t blue = colors[actualColor][2];
  Serial.print("Led color: ");
  Serial.print(red);
  Serial.print(",");
  Serial.print(green);
  Serial.print(",");
  Serial.println(blue);  
  strip.setPixelColor(0, red, green, blue);
  strip.setPixelColor(1, red, green, blue);
  strip.setPixelColor(2, red, green, blue);
  strip.show();
}

