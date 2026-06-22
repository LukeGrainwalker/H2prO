#include "LED.hpp"

Color::Color(int r, int g, int b) {
    red = r & 0xFF;
    green = g & 0xFF;
    blue = b & 0xFF;
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

LED::LED(int pin, enum LEDStatus init_status) {
    src_pin = pin;
    status = init_status;
}

void LED::on() {}
void LED::off() {}

void RGBLed::set_color(int r, int g, int b) {
    // change color
    color.red = r & 0xFF;
    color.green = g & 0xFF;
    color.blue = b & 0xFF;
    
    update();   
}

void RGBLed::update() {
    // write color to led
    int real_r = color.red,
    real_g = color.green,
    real_b = color.blue;

    if (get_type() == COMMON_ANODE) {
        real_r = 255 - r;
        real_g = 255 - g;
        real_b = 255 - b;
    }

    analogWrite(pin_r, real_r & 0xff);
    analogWrite(pin_g, real_g & 0xff);
	analogWrite(pin_b, real_b & 0xff);
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

void RGBLed::set_type(enum LEDType new_type) { type = new_type; }
enum LEDType RGBLed::get_type() { return type; }