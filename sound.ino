#define get_freq(freq) (1000000 / freq)
#define CHANNELS 1
typedef int freq;
typedef unsigned long long time;

struct channel {
  time next;
  freq freq;
};

channel Ch[CHANNELS];

void setup (void) {
  pinMode (13, OUTPUT);
  Ch[0].freq = get_freq(440);
  Ch[1].freq = get_freq(523.25);
}

bool last_state = false;
time now;

void loop (void) {
  now = micros ();
  for (char i = 0; i != CHANNELS; i++) {
    if (Ch[i].next <= now) {
      digitalWrite (13, (last_state = !last_state));
      Ch[i].next = now + Ch[i].freq;
    }
  }
}
