#include "Song.h"
void Song::songTick (void) {  
  if (ended) return;
  
  now = millis();
  if (now >= nextTime) {;
    curPos++;
    
    if (curSong[curPos].cmd >= 0) {
      soundObj->Ch[curSong[curPos].cmd].interval = curSong[curPos].arg;
    }
    
    else {
      switch (curSong[curPos].cmd) {

	case SONG_WAIT:
	  nextTime = now + curSong[curPos].arg;
	  break;

	  
	case SONG_SETDELAY:
	  curDelay = curSong[curPos].arg;
	  break;
	  
	case SONG_LOOP:
	  curPos = 0;
	  break;

	case SONG_END:
	  ended = true;
	  break;

      }
      return;
    }
    nextTime = now + curDelay;
  }
}

void Song::init (Sound* sound) {
  soundObj = sound;
}

void Song::playSong (song_t* song) {
  curSong = song;
}
