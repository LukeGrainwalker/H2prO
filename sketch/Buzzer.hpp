#ifndef BUZZER_HPP
#define BUZZER_HPP

#include <Arduino.h>
#include "Sequence.hpp"

class Buzzer {
private:
  int pin;
  bool paused;
  Sequence seq;
  
public:
  Buzzer();
  void init(int _pin);
  void play();
  void stop();
  void update(unsigned long time);
  void set_sequence(Sequence _seq);
};

#endif