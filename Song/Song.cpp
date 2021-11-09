#include "Song.h"
void Song::songTick (void) {  
  if (this->ended) return;
  
  this->now = millis();
  if (this->now >= this->nextTime) {;
    this->curPos++;
    
    if (this->curSong[this->curPos].cmd >= 0) {
      this->soundObj->Ch[this->curSong[this->curPos].cmd].interval = this->curSong[this->curPos].arg;
    }
    
    else {
      switch (this->curSong[this->curPos].cmd) {

	case SONG_WAIT:
	  this->nextTime = this->now + this->curSong[this->curPos].arg;
	  break;

	  
	case SONG_SETDELAY:
	  this->curDelay = this->curSong[this->curPos].arg;
	  break;
	  
	case SONG_LOOP:
	  this->curPos = 0;
	  break;

	case SONG_END:
	  this->ended = true;
	  break;

      }
      return;
    }
    this->nextTime = this->now + this->curDelay;
  }
}

void Song::init (Sound* sound) {
  this->soundObj = sound;
}

void Song::playSong (song_t* song) {
  this->curSong = song;
}
