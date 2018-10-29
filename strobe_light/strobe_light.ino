// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      80

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int NUM_MILLISECONDS_PER_SECOND = 1000;
int FREQUENCY = 2; // in Hz
int DELAY_VAL = (int) (1/FREQUENCY * 1/2 * 1000); // delay for half a second

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
}

void setAndShowAll(Adafruit_NeoPixel pixels, uint8_t red, uint8_t green, uint8_t blue) {
  for(int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(red, green, blue));
  }
  pixels.show();
}

void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

  for(int i=0;i < NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    setAndShowAll(pixels, 0, 150, 150);
    delay(DELAY_VAL);
    pixels.clear();
    delay(DELAY_VAL);

  }
}
