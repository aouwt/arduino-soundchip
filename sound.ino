#pragma GCC push_options
  #pragma GCC optimize ("Os")
  
  #include <Complex.h>
  
  #define get_freq(freq) (1000000.0 / (freq))
  #define st_to_freq(note) (powf(2, (float)((note) - 49.0) / 12.0) * 440.0)
  #define NOTE(n) get_freq(st_to_freq((n)))
  #define CHANNELS 3
  #define PIN 13
  
  //#define _AMP
  //#define AMP_PIN 12
  //#define AMP_STATE HIGH
  
  #ifndef AMP_PIN
    #undef _AMP
  #endif
  
  #if CHANNELS > 127
    #error Can't have more than 127 channels!
  #endif
  
  #define CMD_WAIT  -1
  #define CMD_LOOP  -2
  #define CMD_END   -3
  
  #define CMD_SETDELAY -10
  
  typedef int freq;
  typedef unsigned long time;
  
  struct song_t {
    int8_t cmd;
    int16_t arg;
  };
  
  struct channel {
    time next;
    freq freq;
    bool cycle;
    #ifdef _AMP
      bool vol = true;
    #endif
  };
  
  
  const struct song_t sng[] = {
    { CMD_SETDELAY, 300 },
    { 0, NOTE(49) },
    { 1, NOTE(52) },
    { 2, NOTE(54) },
    { 0, 0 },
    { 1, 0 },
    { 2, 0 },
    { CMD_LOOP }
  };
  
  
  channel Ch[CHANNELS];
  
  
  void setup (void) {
    pinMode (PIN, OUTPUT);
    #ifdef _AMP
      pinMode (AMP_PIN, OUTPUT);
    #elif defined(AMP_PIN)
      pinMode (AMP_PIN, OUTPUT);
      digitalWrite (AMP_PIN, AMP_STATE);
    #endif
  
    for (unsigned char i = 0; i != CHANNELS; i++)
      play_song();
  }
#pragma GCC pop_options




#pragma GCC push_options
  #pragma GCC optimize ("Ofast")
  void loop (void) {
    update_chs();
    play_song();
  }
#pragma GCC pop_options




#pragma GCC push_options
  #pragma GCC optimize ("Ofast")
  inline void update_chs (void) {
    static time now;
    static unsigned char i;
    if (++i == CHANNELS) {
      i = 0; now = micros();
    }
    if (Ch[i].freq) {
        
      #ifdef _AMP
        digitalWrite (AMP_PIN, Ch[i].vol);
      #endif
        
      digitalWrite (PIN, Ch[i].cycle);
      if (Ch[i].next <= now) {
        Ch[i].cycle = !Ch[i].cycle;
        Ch[i].next = now + Ch[i].freq;
      }
      
    } else digitalWrite (PIN, LOW);
  } 
#pragma GCC pop_options



/*inline void update_chs (void) {
  static time now;
  static bool cycle;
  now = micros();
  for (unsigned char i = 0; i != CHANNELS; i++) {
    
    if (Ch[i].freq) {
      if (Ch[i].next <= now) {
        digitalWrite (PIN, (cycle = !cycle));
        Ch[i].next = now + Ch[i].freq;
      }
    }
    
  }
}*/


#pragma GCC push_options
  #pragma GCC optimize ("Ofast")
  inline void play_song () {
    static time now, next_time;
    static unsigned int ptr = -1;
    static unsigned int cmd_delay = 0;
    static bool ended = false;
    
    if (ended) return;
    
    now = millis();
    if (now >= next_time) {;
      ptr++;
      if (sng[ptr].cmd >= 0) {
        
        #ifdef _AMP
        
          static unsigned char ch;
          ch = sng[ptr].cmd;
          if (sng[ptr].cmd >= 64) {
            ch -= 64;
            Ch[ch].vol = false;
          } else
            Ch[ch].vol = true;
          Ch[ch].freq = sng[ptr].arg;
          
        #else
        
          Ch[sng[ptr].cmd].freq = sng[ptr].arg;
          
        #endif
      }
      else {
        switch (sng[ptr].cmd) {
  
          case CMD_WAIT:
            next_time = now + sng[ptr].arg;
            break;
  
            
          case CMD_SETDELAY:
            cmd_delay = sng[ptr].arg;
            break;
            
          case CMD_LOOP:
            ptr = 0;
            break;
  
          case CMD_END:
            ended = true;
            break;
  
        }
        return;
      }
      next_time = now + cmd_delay;
    }
  }
#pragma GCC pop_options
