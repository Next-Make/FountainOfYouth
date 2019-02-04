/*  
  Required Connections
  --------------------  
    pin 2:  LED Strip #1    OctoWS2811 drives 8 LED Strips.
    pin 14: LED strip #2    All 8 are the same length.
    pin 7:  LED strip #3
    pin 8:  LED strip #4    A 100 ohm resistor should used
    pin 6:  LED strip #5    between each Teensy pin and the
    pin 20: LED strip #6    wire to the LED strip, to minimize
    pin 21: LED strip #7    high frequency ringining & noise.
    pin 5:  LED strip #8
    pin 15 & 16 - Connect together, but do not use
    pin 4 - Do not use
    pin 3 - Do not use as PWM.  Normal use is ok.

  This test is useful for checking if your LED strips work, and which
  color config (WS2811_RGB, WS2811_GRB, etc) they require.
*/

#include <OctoWS2811.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#define RED    0xAA0000
#define GREEN  0x00FF00
#define BLUE   0x0000FF
#define YELLOW 0xFFFF00
#define PINK   0xFF1088
#define ORANGE 0xE05800
//#define WHITE  0xFFFFFF
#define BLACK  0x000000

// Less intense...
//#define RED    0x160000
//#define GREEN  0x001600
//#define BLUE   0x000016
//#define YELLOW 0x101400
//#define PINK   0x120009
//#define ORANGE 0x100400
#define WHITE  0xFFFFFF

#define MAX_FREQ 62
#define MIN_FREQ 58
#define LEDS_PER_STRIP 60
#define LED_FREQ 60 // Hz

#define PUMP_PIN 9


/*
 * Global Variables
 */

DMAMEM int displayMemory[LEDS_PER_STRIP * 6];
int drawingMemory[LEDS_PER_STRIP * 6];

const int config = WS2811_GRB | WS2811_800kHz;

int ledPeriod;

OctoWS2811 leds(LEDS_PER_STRIP, displayMemory, drawingMemory, config);

elapsedMicros redTimer;
elapsedMicros blueTimer;
elapsedMillis pumpTimer;
bool ledOn;
int pumpFreq = 10;
int pumpPeriod;
int redPeriod = 1000000 / (LED_FREQ + 2);
int bluePeriod = 1000000 / (LED_FREQ - 2);


/*
 * Helper Methods
 */

void turnLedsOn() {
  for(int i = 0; i < leds.numPixels(); i++) {
    leds.setPixel(i, WHITE);
  }
  leds.show();
}

void turnLedsOnColor(int color) {
  for(int i = 0; i < leds.numPixels(); i++) {
    leds.setPixel(i, color);
  }
  leds.show();
}

void turnLedsOff() {
  for(int i = 0; i < leds.numPixels(); i++) {
    leds.setPixel(i, BLACK);
  }
  leds.show();
}
int ledColor;

void setup() {
  leds.begin();
  turnLedsOn();
  leds.show();
  pinMode(PUMP_PIN, OUTPUT);
  ledOn = true;
  ledPeriod = 1000000 / LED_FREQ; // period in microseconds because ledTimer is an elapsedMicros
  pumpPeriod = 1000 / pumpFreq;
  digitalWrite(PUMP_PIN, HIGH);
  ledColor = 0;
}

int ledState = 0; // 0 = none on, 0xff0000 = red on, 0x0000ff = blue one, 0xff00ff = both on
int newLedState = 0;

void loop() {
  newLedState = 0;
  if(redTimer < redPeriod / 1000) {
    newLedState += 0xaa0000;
  } else if (redTimer >= redPeriod) {
    redTimer = 0;
  }

  if(blueTimer < bluePeriod / 1000) {
    newLedState += 0x0000ff;
  } else if (blueTimer >= bluePeriod) {
    blueTimer = 0;
  }

  if(newLedState != ledState) {
    turnLedsOnColor(newLedState);
  }
  ledState = newLedState;
  
  if(pumpTimer < pumpPeriod / 2) { // 50% duty cycle
    digitalWrite(PUMP_PIN, HIGH);
  } else if (pumpTimer < pumpPeriod) {
    digitalWrite(PUMP_PIN, LOW);
  } else {
    pumpTimer = 0;
  }
}
