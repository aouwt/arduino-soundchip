/*
  Song.h - Library for controlling sound channels from Sound.h in an easy-to-use API.
  Created by aouwt, November 9, 2021.
  License TBD.
*/
#ifndef Song_h
#define Song_h

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
    typedef unsigned long long time_t;

    typedef struct song_t {
      int8_t cmd;
      uint16_t arg;
    } song_t;

    const song_t* curSong;
    bool isEnded = false;
    
    void restart (void);
    void begin (Sound::channelid_t chs, Sound::pin_t pin);
    void manualBegin (Sound* sound);
    void playSong (const song_t* song);
    void songTick (void);
    void __attribute__((always_inline)) tick (void);
    void setTickType (char tickType);
    void end (void);
    void clearChs (void);
	

  private:
    time_t _now, _nextTime;
    size_t _curPos = 0;
    unsigned int _curDelay = 0;
    Sound* _Sound;

};
#endif
