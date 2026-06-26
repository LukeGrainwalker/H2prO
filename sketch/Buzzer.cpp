#include "Buzzer.hpp"
#include "Sequence.hpp"

void Buzzer::init(int _pin) {
  pin = _pin;
  noTone(pin);
}

void Buzzer::set_sequence(Sequence _seq) { seq = _seq; }

void Buzzer::stop() {
  paused = true;
  noTone(pin);
}

void Buzzer::play() { paused = false; }

void Buzzer::update(unsigned long time) {
  if (paused) {
    return;
  }

  SequenceItem* next = seq.getby_time(time);
  int freq = *(int*)next->data;
  tone(pin, freq, next->duration);
}