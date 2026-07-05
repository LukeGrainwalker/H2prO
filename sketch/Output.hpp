#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <Arduino.h>
#include "Buzzer.hpp"
#include "LED.hpp"
#include "H2prO.hpp"
#include "Sequence.hpp"
#include "colors.hpp"
#include "sequences.hpp"

class Output {
private:
  enum emotion current_emotion;
  RGBLed* rgb_led;
  Buzzer* buzzer;

  Sequence** sequences;
  Sequence* rgb_led_seq;
  Sequence* buzzer_seq;
  // Servo* servo;

public:
  int process_emotion(enum emotion em);
  void init(Sequence** _sequences, RGBLed* _rgb_led, Buzzer* _buzzer);
  void update(unsigned long time);
  void update_buzzer(unsigned long time);
  void update_rgb_led(unsigned long time);

};
#endif