#include <Sound.h>
#include <Song.h>

Sound sound;
Song song;

const Song::song_t playMe[] = {
  { 0, freqToInterval(440) },
  { SONG_END, 0 }
};

void setup() {
  // put your setup code here, to run once:
  sound.init (10, 13);
  sound.Ch[0].interval = freqToInterval(440);
  song.init (&sound);
  song.playSong (playMe);
}

void loop() {
  // put your main code here, to run repeatedly:
  sound.soundTick();
  song.songTick();
}
