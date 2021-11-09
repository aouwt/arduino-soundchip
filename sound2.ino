#include <Song.h>

Song song;

#define N(note) stToInterval(note)
const Song::song_t playMe[] = {
  { SONG_SETDELAY, 100 },
  { 0, N(49) },
  { 1, N(52) },
  { SONG_WAIT, 300 },
  { 1, 0 },
  { 0, 0 },
  { SONG_LOOP, 0 }
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
