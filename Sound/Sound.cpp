#include "Sound.h"

void Sound::begin (Sound::channelid_t chs, Sound::pin_t outputPin) {
  pinMode (outputPin, OUTPUT);
  setTickType (TickType::Full);
  init (chs);
  setPin (outputPin);
  clearChs ();
}

void Sound::clearChs (void) {
  for (channelid_t i = 0; i != numOfChs; i++) {
    ch[i].cycle = false; ch[i].next = 0; ch[i].interval = 0;
  }
  _curCh = 0; _now = 0;
}

void Sound::init (Sound::channelid_t chs) {
  numOfChs = chs;
  ch = (Sound::channel_t*) malloc (sizeof(Sound::channel_t) * chs);
}

void Sound::setPin (Sound::pin_t outputPin) {
  pin = outputPin;
}

void Sound::end (void) {
  free (ch);
}

void /*__attribute__((always_inline))*/ Sound::setFreq (Sound::channelid_t channel, Sound::freq_t freq) {
  ch[channel].interval = freqToInterval (freq);
}

void Sound::setTickType (TickType type) {
  switch (type) {
    case TickType::Normal:
      _tickType = &Sound::tick_Normal;
      break;
    case TickType::Full:
      _tickType = &Sound::tick_Full;
      break;
    case TickType::NormalEQ:
      _tickType = &Sound::tick_NormalEQ;
      break;
    case TickType::FullEQ:
      _tickType = &Sound::tick_FullEQ;
      break;
  }
}

void Sound::tick (void) {
  (this ->* _tickType) ();
}

void Sound::tick_Normal (void) {
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

void Sound::tick_Full (void) {
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

void Sound::tick_NormalEQ (void) {
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

void Sound::tick_FullEQ (void) {
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
