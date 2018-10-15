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

void setup() {
  AudioMemory(12);
//  AudioMemory(15);
  waveform1.begin(WAVEFORM_SINE);
  waveform1.frequency(440);
  waveform1.amplitude(0.3);
}

void loop() {
  for(int i = 220; i < 441; i++){
    waveform1.frequency(i);
    delay(50);
  }
  
  for(int i = 440; i > 219; i--){
    waveform1.frequency(i);
    delay(50);
  }
}

// Teensyduino 1.35 & earlier had a problem with USB audio on Macintosh
// computers.  For more info and a workaround:
// https://forum.pjrc.com/threads/34855-Distorted-audio-when-using-USB-input-on-Teensy-3-1?p=110392&viewfull=1#post110392
