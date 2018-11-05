// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

AudioSynthWaveform       waveform1;      //xy=110,75
AudioOutputI2S           i2s1;           //xy=365,94
AudioConnection          patchCord1(waveform1, 0, i2s1, 0);
AudioConnection          patchCord2(waveform1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=302,184

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      80

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
//
int NUM_MILLISECONDS_PER_SECOND = 1000;
float FREQUENCY = 100; // in Hz
int DELAY_VAL = (int) (1/FREQUENCY * 1/2 * NUM_MILLISECONDS_PER_SECOND); // delay for half a second

void setup() {
  Serial.begin(9600);
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.clear();
  pixels.show();
  AudioMemory(120);
//  AudioMemory(15);
  waveform1.begin(WAVEFORM_SINE);
  waveform1.frequency(440);
  waveform1.amplitude(0.3);
  waveform1.frequency(441);
  pinMode(11, OUTPUT);
}

void setAndShowAll(uint8_t red, uint8_t green, uint8_t blue) {
  pixels.clear();
  for(int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(red, green, blue));
//    Serial.println(i);
  }
  pixels.show();
  Serial.println("Showed pixels");
}

void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
//    delay(500);
    digitalWrite(11, HIGH);
//    delay(500);
    digitalWrite(11, LOW);
    pixels.setPixelColor(4, pixels.Color(0, 0, 255));
//    pixels.show();
    Serial.println("yeet");
//      setAndShowAll(50, 0, 0);
//      Serial.println("set all pixels to red");
//      delay(DELAY_VAL);
//      setAndShowAll(0, 0, 50);
//      Serial.println("set all pixels to green");
//      delay(DELAY_VAL);
}
