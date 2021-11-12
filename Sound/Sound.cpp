#include "Sound.h"

void Sound::begin (Sound::channelid_t chs, Sound::pin_t outputPin) {
  pinMode (outputPin, OUTPUT);
  init (chs);
  setPin (outputPin);
  
  for (channelid_t i = 0; i != chs; i++) {
    ch[i].cycle = false; ch[i].next = 0; ch[i].interval = 0;
  }
  _curCh = 0; _now = 0;
}

void Sound::init (Sound::channelid_t chs) {
  numOfChs = chs;
  ch = new Sound::channel_t[chs];
}

void Sound::setPin (Sound::pin_t outputPin) {
  pin = outputPin;
}

void Sound::end (void) {
  free (ch);
}

void __attribute__((always_inline)) Sound::setFreq (Sound::channelid_t channel, Sound::freq_t freq) {
  ch[channel].interval = freqToInterval (freq);
}

void Sound::tick (void) {
  channelid_t i = numOfChs;
  next:
  if (++_curCh == numOfChs) {
    _curCh = 0; _now = micros ();
  }
  if (ch[_curCh].interval) {
    
    digitalWrite (pin, ch[_curCh].cycle);
    if (ch[_curCh].next <= _now) {
      ch[_curCh].cycle = !ch[_curCh].cycle;
      ch[_curCh].next = _now + ch[_curCh].interval;
    }
    
  } else
    if (i--) goto next;
}

void Sound::fullTick (void) {
  _now = micros ();
  for (_curCh = 0; _curCh != numOfChs; _curCh++) {
    if (ch[_curCh].interval) {
    
      digitalWrite (pin, ch[_curCh].cycle);
      if (ch[_curCh].next <= _now) {
        ch[_curCh].cycle = !ch[_curCh].cycle;
        ch[_curCh].next = _now + ch[_curCh].interval;
      }
    
    }
  }
  digitalWrite (pin, LOW);
}

void Sound::tickEQ (void) {
  if (++_curCh == numOfChs) {
    _curCh = 0; _now = micros ();
  }
  if (ch[_curCh].interval) {
    
    digitalWrite (pin, ch[_curCh].cycle);
    if (ch[_curCh].next <= _now) {
      ch[_curCh].cycle = !ch[_curCh].cycle;
      ch[_curCh].next = _now + ch[_curCh].interval;
    }
    
  } else digitalWrite (pin, LOW);
}

void Sound::fullTickEQ (void) {
  _now = micros ();
  for (_curCh = 0; _curCh != numOfChs; _curCh++) {
    if (ch[_curCh].interval) {
    
      digitalWrite (pin, ch[_curCh].cycle);
      if (ch[_curCh].next <= _now) {
        ch[_curCh].cycle = !ch[_curCh].cycle;
        ch[_curCh].next = _now + ch[_curCh].interval;
      }
    
    } else digitalWrite (pin, LOW);
  }
  digitalWrite (pin, LOW);
}
