/*
  Sound.h - Library for generating multi-channel sound.
  Created by aouwt, November 9, 2021.
  License TBD.
*/

#ifndef Sound_h
#define Sound_h

#include "Arduino.h"

#define TICK_NORMAL 0
#define TICK_FULL 1
#define TICK_NORMALEQ 2
#define TICK_FULLEQ 3

#define freqToInterval(freq) (1000000.0 / (freq))

class Sound {
  public:
    typedef unsigned int fint_t;
    typedef unsigned long time_t;
    typedef unsigned int freq_t;
    typedef unsigned char channelid_t;
    typedef unsigned char pin_t;
    
    enum struct TickType { Normal, Full, NormalEQ, FullEQ };

    typedef struct channel_t {
      fint_t interval;
      time_t next;
      bool cycle = false;
    } channel_t;
    
    channel_t* ch;
    channelid_t numOfChs;
    pin_t pin;
    
    void begin (channelid_t chs, pin_t outputPin);
    void end (void);
    void clearChs (void);
    void setPin (pin_t outputPin);
    void init (channelid_t chs);
    void tick (void);
    void /*__attribute__((always_inline))*/ setFreq (channelid_t channel, freq_t freq);
    void setTickType (TickType type);
    
    void tick_Normal (void);
    void tick_Full (void);
    void tick_NormalEQ (void);
    void tick_FullEQ (void);
    
  protected:
    time_t _now;
    channelid_t _curCh;
    void (Sound::*_tickType) (void);
};
#endif
