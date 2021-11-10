#include <Song.h>

Song song;

#define N(note) stToInterval(note)
const Song::song_t playMe[] = {
  { SONG_SETDELAY, 500 },
  { 0, N(49) },
  { 1, N(53) },
  { 2, N(56) },
  { 3, N(61) },
  { 4, N(65) },
  { 5, N(68) },
  { SONG_WAIT, 1000 },
  { 5, 0 },
  { 4, 0 },
  { 3, 0 },
  { 2, 0 },
  { 1, 0 },
  { 0, 0 },
  { SONG_LOOP, 0 }
};

void setup() {
  // put your setup code here, to run once:
  song.begin (6, 13);
  song.playSong (playMe);
}

void loop() {
  // put your main code here, to run repeatedly:
  song.setTickType (TICK_NORMAL);
  for (uint16_t i = 1; i; i++)
    song.tick();
  song.setTickType (TICK_FULL);
  for (uint16_t i = 1; i; i++)
    song.tick();
    
}
