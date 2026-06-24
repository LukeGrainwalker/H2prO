#include "Buzzer.hpp"

void Buzzer::init(int _pin) {
    pin = _pin;
    noTone(pin);
}

void Buzzer::set_sequence(struct ToneSequence _seq) {
    seq = _seq;
}

void Buzzer::stop() {
    paused = true;
    noTone(pin);
}

void Buzzer::play() {
    paused = false;
}

void Buzzer::check_tone(unsigned long time) {
    if (paused) return;
    if (current_posistion == (seq.length-1) && !seq.loop) {
        return;
    }

    unsigned int time_passed = time - last_checked;
    bool do_next_tone = time_passed > seq.tones[current_posistion].duration + seq.pause_between;
    
    if (do_next_tone) {
        current_posistion = (current_posistion+1) % seq.length;
        
        tone(
            pin, seq.tones[current_posistion].freq,
            seq.tones[current_posistion].duration
        );
    }
}