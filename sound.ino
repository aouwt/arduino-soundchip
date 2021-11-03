#define get_freq(freq) (1000000 / freq)
#define CHANNELS 10
#define PIN 12
typedef int freqtype;
typedef unsigned long long time;

struct channel {
  time next;
  freqtype freq;
  bool cycle;
};

channel Ch[CHANNELS] = {0};

void setup (void) {
  pinMode (PIN, OUTPUT);
  Ch[0].freq = get_freq(440);
  Ch[1].freq = get_freq(572.25);
}
bool last_state = false;
time now;

void loop (void) {
  now = micros ();
  for (char i = 0; i != CHANNELS; i++) {
    if (Ch[i].freq) {
      digitalWrite (PIN, Ch[i].cycle);
      if (Ch[i].next <= now) {
        Ch[i].cycle = !Ch[i].cycle;
        Ch[i].next = now + Ch[i].freq;
      }
    }
  }
}
