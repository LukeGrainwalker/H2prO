#ifndef BUZZER_HPP
#define BUZZER_HPP

#include <Arduino.h>

struct Tone {
    int duration;
    int freq;
};

struct ToneSequence {
    bool loop;
    Tone* tones;
    int length;
    unsigned int pause_between;
};

class Buzzer {
  private:
    int pin;
    bool paused;
    ToneSequence seq;
    int current_posistion;
    bool finished;
    unsigned long last_checked;
  public:
    Buzzer();
    void init(int _pin);
    void play();
    void stop();
    void check_tone(unsigned long time);
    void set_sequence(struct ToneSequence);
};

#endif