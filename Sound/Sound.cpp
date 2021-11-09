#include "Sound.h"

void Sound::init (Sound::channelid_t chs, Sound::pin_t pin) {
  pinMode (pin, OUTPUT);
  this->NumOfChs = chs;
  this->Pin = pin;
  this->Ch = (Sound::channel_t*) malloc (sizeof(Sound::channel_t) * chs);
  return;
}

void Sound::drop (void) {
  free (this->Ch);
  return;
}

void Sound::setFreq (Sound::channelid_t ch, Sound::freq_t freq) {
  this->Ch[ch].interval = freqToInterval (freq);
  return;
}

void Sound::soundTick (void) {
  if (++this->curCh == this->NumOfChs) {
    this->curCh = 0; this->now = micros();
  }
  if (this->Ch[this->curCh].interval) {
    
    digitalWrite (this->Pin, this->Ch[this->curCh].cycle);
    if (this->Ch[this->curCh].next <= this->now) {
      this->Ch[this->curCh].cycle = !this->Ch[this->curCh].cycle;
      this->Ch[this->curCh].next = this->now + this->Ch[this->curCh].interval;
    }
    
  } else digitalWrite (this->Pin, LOW);
}
