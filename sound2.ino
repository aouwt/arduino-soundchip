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
  { SONG_WAIT, 1000 },
  { SONG_END, 0 }
};

void setup() {
  // put your setup code here, to run once:
  song.begin (6, 13);
  song.playSong (playMe);
}

void loop() {
  // put your main code here, to run repeatedly:
  song.restart ();
  song.setTickType (TICK_NORMAL);
  while (!song.isEnded)
    song.tick ();
  
  song.restart ();
  song.setTickType (TICK_FULL);
  while (!song.isEnded)
    song.tick ();
  
  song.restart ();
  song.setTickType (TICK_NORMALEQ);
  while (!song.isEnded)
    song.tick ();
  
  song.restart ();
  song.setTickType (TICK_FULLEQ);
  while (!song.isEnded)
    song.tick ();
}
