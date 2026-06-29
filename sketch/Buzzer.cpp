#include "Buzzer.hpp"
#include "Sequence.hpp"

Buzzer::Buzzer() {}

void Buzzer::init(int _pin) {
  pin = _pin;
  noTone(pin);
}

void Buzzer::stop() {
  paused = true;
  noTone(pin);
}

void Buzzer::play() {
  paused = false;
}

int Buzzer::ensure_tone(int _freq, int duration) {
  if (paused) return 0;

  if (_freq != current_tone) {
    current_tone = _freq;
    tone(pin, _freq, duration);
    return 1;
  }

  return 0;
}