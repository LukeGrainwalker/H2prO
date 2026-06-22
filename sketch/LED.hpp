#ifndef LED_HPP
#define LED_HPP

#include <Arduino.h>

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
  RGBLed(int p_r, int p_g, int p_b);

  void on();
  void off();
  void update();
  enum LEDType get_type();
  void set_type(enum LEDType);

  // color setting
  void set_color(Color clr);
  void set_color(int r, int g, int b);

  // state management
  int ensure_color(Color clr);
  int ensure_state(int state, Color clr);
};

#endif