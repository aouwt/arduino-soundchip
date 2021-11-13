#include "Song.h"

void Song::songTick (void) {  
  if (isEnded) return;
  
  _now = millis ();
  if (_now >= _nextTime) {
  
    if (curSong[_curPos].cmd >= 0) {
      _Sound -> ch[curSong[_curPos].cmd].interval = curSong[_curPos].arg;
    }
    
    else {
      switch (curSong[_curPos].cmd) {

	case SONG_WAIT:
	  _nextTime = _now + curSong[_curPos].arg;
	  break;

	  
	case SONG_SETDELAY:
	  _curDelay = curSong[_curPos].arg;
	  break;
	  
	case SONG_LOOP:
	  _curPos = 0;
	  break;

	case SONG_END:
	  isEnded = true;
	  break;

      }
      _curPos++; return;
    }
    _nextTime = _now + _curDelay;
    _curPos++;
  }
}

void Song::manualBegin (Sound* sound) {
  _Sound = sound;
}

void Song::begin (Sound::channelid_t chs, Sound::pin_t pin) {
  _Sound = (Sound*) malloc (sizeof(Sound));
  _Sound -> begin (chs, pin);
  setTickType (TICK_FULL);
}

void Song::end (void) {
  _Sound -> end ();
  free (_Sound);
}

void Song::playSong (const Song::song_t* song) {
  isEnded = false;
  curSong = song;
}

void Song::restart (void) {
  isEnded = false;
  _nextTime = 0;
  _curPos = -1;
  _curDelay = 0;
  clearChs ();
}

void Song::clearChs (void) {
  for (Sound::channelid_t i = 0; i != _Sound -> numOfChs; i++) {
    _Sound -> ch[i].cycle = false;
    _Sound -> ch[i].next = 0;
    _Sound -> ch[i].interval = 0;
  }
}

void __attribute__((always_inline)) Song::tick (void) {
  songTick ();
  _Sound -> tick ();
}
