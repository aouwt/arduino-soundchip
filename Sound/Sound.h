/*
  Sound.h - Library for generating multi-channel sound.
  Created by aouwt, November 9, 2021.
  License TBD.
*/

#ifndef Sound_h
#define Sound_h

#include "Arduino.h"

#define freqToInterval(freq) ((Sound::fint_t)(1000000.0 / (freq)))

class Sound {
  public:
    typedef unsigned int fint_t;
    typedef unsigned long time_t;
    typedef unsigned int freq_t;
    typedef unsigned char channelid_t;
    typedef unsigned char pin_t;

    typedef struct channel_t {
      fint_t interval = 0;
      time_t next = 0;
      bool cycle = false;
    } channel_t;
    
    channel_t* ch;
    channelid_t numOfChs;
    pin_t pin;
    
    void begin (channelid_t chs, pin_t outputPin);
    void end (void);
    void soundTick (void);
    void setFreq (channelid_t channel, freq_t freq);
    
  private:
    time_t _now;
    channelid_t _curCh;
};
#endif