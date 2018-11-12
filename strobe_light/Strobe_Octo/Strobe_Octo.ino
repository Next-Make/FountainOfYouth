/*  OctoWS2811 BasicTest.ino - Basic RGB LED Test
    http://www.pjrc.com/teensy/td_libs_OctoWS2811.html
    Copyright (c) 2013 Paul Stoffregen, PJRC.COM, LLC

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.

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
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

AudioSynthWaveform       waveform1;      //xy=110,75
AudioOutputI2S           i2s1;           //xy=365,94
AudioConnection          patchCord1(waveform1, 0, i2s1, 0);
AudioConnection          patchCord2(waveform1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=302,184

const int ledsPerStrip = 120;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_GRB | WS2811_800kHz;

float MAX_FREQ = 30;
float MIN_FREQ = 5;
float FREQUENCY = 60; // in Hz
int NUM_MICROSECONDS_PER_SECOND = 1000000;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

void setup() {
  leds.begin();
  leds.show();
  AudioMemory(12);
  waveform1.frequency(FREQUENCY);
  waveform1.amplitude(.6);
  waveform1.begin(WAVEFORM_SINE);
  pinMode(14, INPUT);
}

//#define RED    0xAA0000
//#define GREEN  0x00FF00
//#define BLUE   0x0000FF
//#define YELLOW 0xFFFF00
//#define PINK   0xFF1088
//#define ORANGE 0xE05800
//#define WHITE  0xFFFFFF
#define BLACK  0x000000

// Less intense...

//#define RED    0x160000
//#define GREEN  0x001600
//#define BLUE   0x000016
//#define YELLOW 0x101400
//#define PINK   0x120009
//#define ORANGE 0x100400
#define WHITE  0X777777

void loop() {
  float pot_val = analogRead(14);
  FREQUENCY = map(pot_val, 0, 1024, MIN_FREQ, MAX_FREQ);
  waveform1.frequency(FREQUENCY);
  int DELAY_VAL = (int) (1/FREQUENCY * 1/2 * NUM_MICROSECONDS_PER_SECOND); // delay for half a second

  Serial.println(DELAY_VAL);
  delayMicroseconds(DELAY_VAL);
  for (int i=0; i<leds.numPixels(); i++){
     leds.setPixel(i, WHITE);
  }
  leds.show();  
  delayMicroseconds(DELAY_VAL);
  for (int i=0; i<leds.numPixels(); i++){
     leds.setPixel(i, BLACK);
  }
  leds.show();
}
