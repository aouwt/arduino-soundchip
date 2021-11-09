#include <Song.h>

Song song;

const Song::song_t playMe[] = {
  { 0, freqToInterval(440) },
  { SONG_END, 0 }
};

void setup() {
  // put your setup code here, to run once:
  song.begin (10, LED_BUILTIN);
  song.playSong (playMe);
}

void loop() {
  // put your main code here, to run repeatedly:
  song.tick();
}
