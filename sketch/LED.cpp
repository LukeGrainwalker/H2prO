#include "LED.hpp"

Color::Color(int r, int g, int b) {
    red = r & 0xFF;
    green = g & 0xFF;
    blue = b & 0xFF;
}

Color::Color() {
    red = 0, green = 0, blue = 0;
}

void Color::set(int r, int g, int b) {
    red = r, green = g, blue = b;
}

void Color::set(Color clr) {
    set(clr.red, clr.green, clr.blue);
}

bool Color::is_equal(int r, int g, int b) {
    if (red == r && green == g && blue == b) {
        return true;
    } else {
        return false;
    }
};

bool Color::is_equal(Color clr) {
    return is_equal(clr.red, clr.green, clr.blue);
}

LED::LED(int _pin) {
    pinMode(pin, OUTPUT);
    pin = _pin;
}

LED::LED(int _pin, bool on_pull_down) : LED(_pin) {
    on_level = !on_pull_down;
}

void LED::on() {
    if (status == LED_OFF) {
        digitalWrite(pin, on_level);
        status = LED_ON;
    }
}

void LED::off() {
    if (status == LED_ON) {
        digitalWrite(pin, !on_level);
        status = LED_OFF;
    }
}

RGBLed::RGBLed(int p_r, int p_g, int p_b) {
    pin_r = p_r;
    pin_g = p_g;
    pin_b = p_b;
}

RGBLed::RGBLed(
    int p_r, int p_g, int p_b,
    Color clr
) : RGBLed(p_r, p_g, p_b) {
    color.set(clr);
}

RGBLed::RGBLed(
    int p_r, int p_g, int p_b,
    Color clr, enum LEDType _type
) : RGBLed(p_r, p_g, p_b, clr) {
    color.set(clr);
    type = _type;
}

void RGBLed::set_color(int r, int g, int b) {
    // change color
    color.red = r & 0xFF;
    color.green = g & 0xFF;
    color.blue = b & 0xFF;
    
    update();
}

void RGBLed::update() {
    Serial.println("update led...");

    // write color to led
    int real_r = color.red,
    real_g = color.green,
    real_b = color.blue;

    if (type == COMMON_ANODE) {
        real_r = 255 - color.red;
        real_g = 255 - color.green;
        real_b = 255 - color.blue;
    }

    analogWrite(pin_r, real_r);
    analogWrite(pin_g, real_g);
	analogWrite(pin_b, real_b);
}

void RGBLed::set_color(Color clr) {
    set_color(clr.red, clr.green, clr.blue);
}

int RGBLed::ensure_state(int required_state, Color clr) {
    if (required_state != state) {
        state = required_state;
        set_color(clr.red, clr.green, clr.blue);
        return 1;
    } else {
        return 0;
    }
}

void RGBLed::print_color() {
    Serial.print("RGBLed color: red=");
    Serial.print(color.red);
    Serial.print(", green=");
    Serial.print(color.green);
    Serial.print(", blue=");
    Serial.println(color.blue);
}

void RGBLed::set_type(enum LEDType new_type) { type = new_type; }

enum LEDType RGBLed::get_type() {
    return type;
}
