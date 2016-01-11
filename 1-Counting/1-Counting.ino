int nixiePins[4] = {5,4,3,2};
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
  for(int i = 0; i < 4; i++)
    pinMode(nixiePins[i], OUTPUT);
}

void loop() {
  
  // loop through all the digits
  for(int j = 0; j < 10; j++) {

    // change the pins accordingly to the number
    for(int i = 0; i < 4; i++)
      digitalWrite(nixiePins[i], bcd[j][i]);

    // delay 500ms
    delay(500);
  }

}
