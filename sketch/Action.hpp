#ifndef ACTION_HPP
#define ACTION_HPP

#include <Arduino.h>
#include "H2prO.hpp"

class Color {
public:
  int red, green, blue;

  Color(int r, int g, int b);
  bool is_equal(Color clr);
  bool is_equal(int r, int g, int b);
};

enum LEDStatus { LED_ON = 0, LED_OFF };
enum LEDType { COMMON_ANODE = 0, COMMON_CATHODE };

class LED {
private:
  int src_pin;
  enum LEDStatus status;
public:
  void on();
  void off();
  LED(int pin, enum LEDStatus init_status);
  LED(int pin, enum LEDStatus init_status, enum LEDType init_type);
  enum LEDStatus get_status();
};

class RGBLed {
private:
  int state;
  int pin_r, pin_g, pin_b;
  Color color;
  enum LEDType type;
public:
  void on();
  void off();
  enum LEDType get_type();

  // color setting
  void set_color(Color clr);
  void set_color(int r, int g, int b);

  // state management
  int ensure_color(Color clr);
  int ensure_state(int state, Color clr);
};

class Buzzer {};

class Action {
public:
  int process_emotion(enum emotion);
};

#endif