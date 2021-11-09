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

#define stToFreq(note) ((uint16_t)(powf(2, (float)((note) - 49.0) / 12.0) * 440.0))
#define stToInterval(note) ((Sound::fint_t)(freqToInterval(stToFreq((note)))))

class Song {
  public:
    typedef unsigned long time_t;

    typedef struct song_t {
      int8_t cmd;
      uint16_t arg;
    } song_t;

    const song_t* curSong;

	void begin (Sound::channelid_t chs, Sound::pin_t pin);
    void manualBegin (Sound* sound);
    void playSong (const song_t* song);
    void songTick (void);
	void tick (void);
	void end (void);
	

  private:
    time_t _now, _nextTime;
    unsigned char _curPos = -1;
    unsigned int _curDelay = 0;
    bool _ended = false;
    Sound* _Sound;
};
#endif