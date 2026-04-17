//this code is for Model 1
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
int i = 0;

int stationCheck = -1;

//data for red light
int redStrip_station0 = 0;
int redStrip_station1 = 2;
int redStrip_station2 = 10;
int redStrip_station3 = 19;
int redStrip_station4 = 26;
int redStrip_station5 = 39;
int redStrip_station6 = 60;
int redStrip_station7 = 78;
int redStrip_station8 = 89;
int redStrip_exit = 100;

//red light is stationary while all other lights come out. so it is used twice
int redStrip_stations[11] = {redStrip_station0, redStrip_station1, redStrip_station1, redStrip_station2, redStrip_station3, redStrip_station4, redStrip_station5, redStrip_station6, redStrip_station7, redStrip_station8, redStrip_exit};

//data for green light
int greenStrip_increment = 2;

//data for blue light
int blueStrip_increment = -2;

//data for orange light (same strip as blue light)
int orangeStrip_increment = 2;

#define SPEED 150           //delay time for each transition

#define greenStrip_PIN 10
#define redStrip_PIN 11
#define blueStrip_PIN 12

#define next_button 9

#define redStrip_NUMPIXELS redStrip_exit
#define greenStrip_NUMPIXELS redStrip_exit
#define blueStrip_NUMPIXELS redStrip_exit

Adafruit_NeoPixel redStrip(redStrip_NUMPIXELS, redStrip_PIN, NEO_GRB + NEO_KHZ800); //defining varible strip
Adafruit_NeoPixel greenStrip(greenStrip_NUMPIXELS, greenStrip_PIN, NEO_GRB + NEO_KHZ800); //defining varible strip
Adafruit_NeoPixel blueStrip(blueStrip_NUMPIXELS, blueStrip_PIN, NEO_GRB + NEO_KHZ800); //defining varible strip

void clear_LEDs() {
  redStrip.clear();
  greenStrip.clear();
  blueStrip.clear();
  redStrip.show();
  greenStrip.show();
  blueStrip.show();
}

void moveLed(uint16_t prevStation, uint16_t nextStation, Adafruit_NeoPixel &strip, uint8_t R, uint8_t G, uint8_t B) {
  for(i=prevStation; i<nextStation; i++) {
    strip.setPixelColor(i+1, strip.Color(R, G, B));
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.show();
    delay(SPEED);
  }
}

void moveALLLed(int prevStation, int nextStation, int R) {
  for(i=prevStation; i<nextStation; i++) {
    redStrip.setPixelColor(i+1, redStrip.Color(R, 0, 0));
    redStrip.setPixelColor(i, redStrip.Color(0, 0, 0));
    greenStrip.setPixelColor(i+1+greenStrip_increment, greenStrip.Color(0, 255, 0));
    greenStrip.setPixelColor(i+greenStrip_increment, greenStrip.Color(0, 0, 0));
    blueStrip.setPixelColor(i+1+blueStrip_increment, blueStrip.Color(0, 0, 255));
    blueStrip.setPixelColor(i+blueStrip_increment, blueStrip.Color(0, 0, 0));
    blueStrip.setPixelColor(i+1+orangeStrip_increment, blueStrip.Color(255, 165, 0)); //orange color
    blueStrip.setPixelColor(i+orangeStrip_increment, blueStrip.Color(0, 0, 0));
    
    blueStrip.show();
    greenStrip.show();
    redStrip.show();
    delay(SPEED);
  }
}

void setup() {
  redStrip.begin();
  greenStrip.begin();
  blueStrip.begin();

  pinMode(next_button, INPUT_PULLUP);
  clear_LEDs();
}


void loop() {
  //when next button is pressed
  if (digitalRead(next_button) == LOW) {
    delay(10);
    if (digitalRead(next_button) == LOW) {
      stationCheck = (stationCheck + 1) % 11;
      if (stationCheck == 0) moveALLLed(redStrip_stations[stationCheck], redStrip_stations[(stationCheck + 1)], 0); //keep red off at the beginning
      else if (stationCheck == 1) moveLed(redStrip_stations[stationCheck-1], redStrip_stations[(stationCheck)], redStrip, 255, 0, 0); //red light comes out at the first station
      else if (stationCheck == 10) clear_LEDs();
      else moveALLLed(redStrip_stations[stationCheck], redStrip_stations[(stationCheck + 1)], 255);
      while (digitalRead(next_button) == LOW) delay(10);
    }
  }
}