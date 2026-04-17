//this code is for Model 1
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
uint16_t i = 0;

//data for green station
uint16_t greenStrip_stationCheck = 0;
uint16_t greenStrip_station0 = 0;
uint16_t greenStrip_station1 = 51;
uint16_t greenStrip_exit = 63;

//data for red01 station
uint16_t redStrip01_stationCheck = 0;
uint16_t redStrip01_station0 = 0;
uint16_t redStrip01_station1 = 31;
uint16_t redStrip01_station2 = 46;
uint16_t redStrip01_station3 = 64;
uint16_t redStrip01_station4 = 78;
uint16_t redStrip01_station5 = 108;
uint16_t redStrip01_exit = 124;

//data for red02 station
uint16_t redStrip02_stationCheck = 0;
uint16_t redStrip02_station0 = 0;
uint16_t redStrip02_station1 = 15;
uint16_t redStrip02_station2 = 31;
uint16_t redStrip02_exit = 62;

//data for blue station
uint16_t blueStrip_stationCheck = 0;
uint16_t blueStrip_station0 = 0;
uint16_t blueStrip_station1 = 40;
uint16_t blueStrip_station2 = 52;
uint16_t blueStrip_station3 = 70;
uint16_t blueStrip_station4 = 89;
uint16_t blueStrip_exit = 106;

#define SPEED 50           //delay time for each transition

#define greenStrip_PIN 12
#define redStrip01_PIN 11
#define redStrip02_PIN 10
#define blueStrip_PIN 9
#define greenStrip_button 8
#define redStrip01_button 7
#define redStrip02_button 6
#define blueStrip_button 5

#define greenStrip_NUMPIXELS greenStrip_exit
#define redStrip01_NUMPIXELS redStrip01_exit
#define redStrip02_NUMPIXELS redStrip02_exit
#define blueStrip_NUMPIXELS blueStrip_exit

Adafruit_NeoPixel greenStrip(greenStrip_NUMPIXELS, greenStrip_PIN, NEO_GRB + NEO_KHZ800); //defining varible strip
Adafruit_NeoPixel redStrip01(redStrip01_NUMPIXELS, redStrip01_PIN, NEO_GRB + NEO_KHZ800); //defining varible strip
Adafruit_NeoPixel redStrip02(redStrip02_NUMPIXELS, redStrip02_PIN, NEO_GRB + NEO_KHZ800); //defining varible strip
Adafruit_NeoPixel blueStrip(blueStrip_NUMPIXELS, blueStrip_PIN, NEO_GRB + NEO_KHZ800); //defining varible strip


void moveLed(uint16_t prevStation, uint16_t nextStation, Adafruit_NeoPixel &strip, uint8_t R, uint8_t G, uint8_t B) {
  for(i=prevStation; i<nextStation; i++) {
    strip.setPixelColor(i+1, strip.Color(R, G, B));
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.show();
    delay(SPEED);
  }
}


void setup() {
  greenStrip.begin();
  redStrip01.begin();
  redStrip02.begin();
  blueStrip.begin();

  pinMode(greenStrip_button, INPUT_PULLUP);
  pinMode(redStrip01_button, INPUT_PULLUP);
  pinMode(redStrip02_button, INPUT_PULLUP);
  pinMode(blueStrip_button, INPUT_PULLUP);

  greenStrip.clear();
  redStrip01.clear();
  redStrip02.clear();
  blueStrip.clear();
}


void loop() {
  //when green button is pressed for green light
  if (digitalRead(greenStrip_button) == LOW) {
    delay(10);
    if (digitalRead(greenStrip_button) == LOW) {
      delay(10);
      greenStrip_stationCheck = (greenStrip_stationCheck + 1) % 2;
      switch (greenStrip_stationCheck){
        case 1:
          greenStrip.clear();
          moveLed(greenStrip_station0, greenStrip_station1, greenStrip, 0, 255, 0);
          break;
        case 0:
          moveLed(greenStrip_station1, greenStrip_exit-1, greenStrip, 0, 255, 0);
          break;
      }
      while (digitalRead(greenStrip_button) == LOW) delay(10);
    }
  }

  //when red1 button is pressed for red light
  if (digitalRead(redStrip01_button) == LOW) {
    delay(10);
    if (digitalRead(redStrip01_button) == LOW) {
      delay(10);
      redStrip01_stationCheck = (redStrip01_stationCheck + 1) % 6;
      switch (redStrip01_stationCheck){
        case 1:
          redStrip01.clear();
          moveLed(redStrip01_station0, redStrip01_station1, redStrip01, 255, 0, 0);
        break;
        case 2:
          moveLed(redStrip01_station1, redStrip01_station2, redStrip01, 255, 0, 0);
        break;
        case 3:
          moveLed(redStrip01_station2, redStrip01_station3, redStrip01, 255, 0, 0);
        break;
        case 4:
          moveLed(redStrip01_station3, redStrip01_station4, redStrip01, 255, 0, 0);
        break;
        case 5:
          moveLed(redStrip01_station4, redStrip01_station5, redStrip01, 255, 0, 0);
        break;
        case 0:
          moveLed(redStrip01_station5, redStrip01_exit-1, redStrip01, 255, 0, 0);
        break;
      }
      while (digitalRead(redStrip01_button) == LOW) delay(10);
    }
  }

    //when red2 button is pressed for red light
    if (digitalRead(redStrip02_button) == LOW) {
      delay(10);
      if (digitalRead(redStrip02_button) == LOW) {
        redStrip02_stationCheck = (redStrip02_stationCheck + 1) % 3;
        switch (redStrip02_stationCheck){
          case 1:
            redStrip02.clear();
            moveLed(redStrip02_station0, redStrip02_station1, redStrip02, 255, 0, 0);
          break;
          case 2:
            moveLed(redStrip02_station1, redStrip02_station2, redStrip02, 255, 0, 0);
          break;
          case 0:
            moveLed(redStrip02_station2, redStrip02_exit-1, redStrip02, 255, 0, 0);
          break;
        }
        while (digitalRead(redStrip02_button) == LOW) delay(10);
      }
    }
    
    //when blue button is pressed for blue light
    if (digitalRead(blueStrip_button) == LOW) { 
      delay(10);
      if (digitalRead(blueStrip_button) == LOW) {
        blueStrip_stationCheck = (blueStrip_stationCheck + 1) % 5;
        switch (blueStrip_stationCheck){
          case 1:
            blueStrip.clear();
            moveLed(blueStrip_station0, blueStrip_station1, blueStrip, 0, 0, 255);
          break;
          case 2:
            moveLed(blueStrip_station1, blueStrip_station2, blueStrip, 0, 0, 255);
          break;
          case 3:
            moveLed(blueStrip_station2, blueStrip_station3, blueStrip, 0, 0, 255);
          break;
          case 4:
            moveLed(blueStrip_station3, blueStrip_station4, blueStrip, 0, 0, 255);
          break;
          case 0:
            moveLed(blueStrip_station4, blueStrip_exit-1, blueStrip, 0, 0, 255);
          break;
        }
        while (digitalRead(blueStrip_button) == LOW) delay(10);
      }
    }
}