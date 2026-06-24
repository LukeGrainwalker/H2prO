#ifndef LED_HPP
#define LED_HPP

#include <Arduino.h>

class Color {
public:
  int red, green, blue;
  Color();
  Color(int r, int g, int b);
  void set(int r, int g, int b);
  void set(Color clr);
  bool is_equal(Color clr);
  bool is_equal(int r, int g, int b);
};

enum LEDStatus { LED_ON = 0, LED_OFF };
enum LEDType { COMMON_ANODE = 0, COMMON_CATHODE };

class LED {
private:
  int pin;
  bool on_level = HIGH;
  enum LEDStatus status = LED_OFF;
public:
  void on();
  void off();
  LED(int _pin);
  LED(int _pin, bool on_pull_down);
  enum LEDStatus get_status();
};

class RGBLed {
private:
  int state;
  int pin_r, pin_g, pin_b;
  Color color;
  enum LEDType type = COMMON_CATHODE;
public:
  RGBLed(int p_r, int p_g, int p_b);
  RGBLed(int p_r, int p_g, int p_b, Color clr);
  RGBLed(int p_r, int p_g, int p_b, Color clr, enum LEDType _type);

  void update();
  enum LEDType get_type();
  void set_type(enum LEDType);

  // color setting
  void set_color(Color clr);
  void set_color(int r, int g, int b);
  void print_color();

  // state management
  int ensure_color(Color clr);
  int ensure_state(int state, Color clr);
};

#endif