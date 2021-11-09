#pragma once
#include "Arduino.h"

#define freqToInterval(freq) (1000000.0 / (freq))

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
    
    channel_t* Ch;
    channelid_t NumOfChs;
    pin_t Pin;
    
    void init (channelid_t NumOfChs, pin_t pin);
    void drop (void);
    void soundTick (void);
    inline void setFreq (channelid_t ch, freq_t freq);
    
  private:
    time_t now;
    channelid_t curCh;
};
