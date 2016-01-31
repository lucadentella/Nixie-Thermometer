#include <Adafruit_NeoPixel.h>

#define BUTTON_PIN   10
#define PIXEL_PIN    14
#define PIXEL_COUNT   1

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
  pinMode(BUTTON_PIN, INPUT);
  strip.begin();
  showActualColor();
}

void loop() {
  
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

