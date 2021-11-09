#include "Song.h"

void Song::songTick (void) {  
  if (_ended) return;
  
  _now = millis();
  if (_now >= _nextTime) {;
    _curPos++;
    
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
	  _ended = true;
	  break;

      }
      return;
    }
    _nextTime = _now + _curDelay;
  }
}

void Song::manualBegin (Sound* sound) {
  _Sound = sound;
}

void Song::begin (Sound::channelid_t chs, Sound::pin_t pin) {
  _Sound = (Sound*) malloc (sizeof(Sound));
  _Sound -> begin (chs, pin);
}

void Song::end (void) {
  _Sound -> end ();
  free (_Sound);
}

void Song::playSong (const song_t* song) {
  curSong = song;
}

void Song::tick (void) {
  this -> songTick ();
  _Sound -> soundTick ();
}