#include "Sound.h"

void Sound::init (Sound::channelid_t chs, Sound::pin_t pin) {
  pinMode (pin, OUTPUT);
  NumOfChs = chs;
  Pin = pin;
  Ch = (Sound::channel_t*) malloc (sizeof(Sound::channel_t) * chs);
  return;
}

void Sound::drop (void) {
  free (Ch);
  return;
}

void Sound::setFreq (Sound::channelid_t ch, Sound::freq_t freq) {
  Ch[ch].interval = freqToInterval (freq);
  return;
}

void Sound::soundTick (void) {
  if (++curCh == NumOfChs) {
    curCh = 0; now = micros();
  }
  if (Ch[curCh].interval) {
    
    digitalWrite (Pin, Ch[curCh].cycle);
    if (Ch[curCh].next <= now) {
      Ch[curCh].cycle = !Ch[curCh].cycle;
      Ch[curCh].next = now + Ch[curCh].interval;
    }
    
  } else digitalWrite (Pin, LOW);
}
