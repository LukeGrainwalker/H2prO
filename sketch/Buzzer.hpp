#ifndef BUZZER_HPP
#define BUZZER_HPP

#include <Arduino.h>

class Buzzer {
private:
  int pin;
  bool paused;
  int current_tone;
  
public:
  Buzzer();
  void init(int _pin);
  void play();
  void stop();
  int ensure_tone(int _freq, int duration);
};

#endif