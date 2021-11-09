#include <Sound.h>
#include <Song.h>

Sound soundObj;
Song songObj;

const Song::song_t playMe[] = {
  { 0, freqToInterval(440) },
  { SONG_END, 0 }
};

void setup() {
  // put your setup code here, to run once:
  soundObj.init (10, 13);
  soundObj.Ch[0].interval = freqToInterval(440);
  //songObj.init (&soundObj);
  //songObj.playSong (playMe);
}

void loop() {
  // put your main code here, to run repeatedly:
  soundObj.soundTick();
  //songObj.songTick();
}
