#include "Sound.h"

void Sound::begin (Sound::channelid_t chs, Sound::pin_t outputPin) {
  pinMode (outputPin, OUTPUT);
  numOfChs = chs;
  pin = outputPin;
  ch = malloc (sizeof(Sound::channel_t) * chs);
}

void Sound::end (void) {
  free (ch);
}

void Sound::setFreq (Sound::channelid_t channel, Sound::freq_t freq) {
  ch[channel].interval = freqToInterval (freq);
}

void Sound::soundTick (void) {
  if (++_curCh == numOfChs) {
    _curCh = 0; _now = micros();
  }
  if (ch[_curCh].interval) {
    
    digitalWrite (pin, ch[_curCh].cycle);
    if (ch[_curCh].next <= _now) {
      ch[_curCh].cycle = !ch[_curCh].cycle;
      ch[_curCh].next = _now + ch[_curCh].interval;
    }
    
  } else digitalWrite (pin, LOW);
}
