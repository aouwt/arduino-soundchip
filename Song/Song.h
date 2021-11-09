#pragma once
#include "Sound.h"
#include "Arduino.h"
#include "Complex.h"

#define SONG_WAIT -1
#define SONG_SETDELAY -2
#define SONG_END -3
#define SONG_LOOP -4

#define stToFreq(note) (powf(2, (float)((note) - 49.0) / 12.0) * 440.0)
#define stToInterval(note) (freqToInterval(stToFreq((note))))

class Song {
  public:
    typedef unsigned long time_t;

    typedef struct song_t {
      int8_t cmd;
      uint16_t arg;
    } song_t;

    song_t* curSong;

    void init (Sound* sound);
    void playSong (song_t* song);
    void songTick (void);

  private:
    time_t now, nextTime;
    unsigned char curPos = -1;
    unsigned int curDelay = 0;
    bool ended = false;
    Sound* soundObj;
};
