#pragma GCC optimize ("Ofast")
#include <Sound.h>

Sound sound;

#define getnote(note) (powf(2, ((float)(note)-49.0)/12.0) * 220.0)

void setup (void) {
  // put your setup code here, to run once:
  sound.begin (8, LED_BUILTIN);
  Serial.begin (9600);
}


void loop (void) {
  sound.tick_Normal ();
  if (Serial.available () >= 3) MIDIRead ();
}

void MIDIRead (void) {
  uint8_t cmd = Serial.read ();
  if ((cmd & 0b10000000) == 0) return;
  uint8_t note = Serial.read ();
  uint8_t vel = Serial.read ();
  
  switch (cmd & 0xF0) {
    
    case 0x80:; // note off
      note_off (note);
      break;
      
    case 0x90:; // note on
      if (vel == 0) note_off (note);
      else note_on (note);
      break;
      
    case 0xC0:; //control
      switch (note) {
        case 121:
        case 123:
          sound.clearChs();
          break;
      }
      break;
  }
}

void note_on (uint8_t note) {
  Sound::fint_t iv = freqToInterval (getnote(note));
  
  for (Sound::channelid_t i = 0; i != sound.numOfChs; i++) {
    
    if (sound.ch[i].interval == 0) {
      sound.ch[i].interval = iv;
      return;
    }
    
  }
  sound.ch[0].interval = iv;
}

void note_off (uint8_t note) {
  Sound::fint_t iv = freqToInterval (getnote(note));

  for (Sound::channelid_t i = 0; i != sound.numOfChs; i++) {
    
    if (sound.ch[i].interval == iv) {
      sound.ch[i].interval = 0;
      return;
    }
    
  }
}
