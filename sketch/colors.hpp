#ifndef COLOR_HPP
#define COLOR_HPP

#include "LED.hpp"

const Color RGB_RED = Color(255, 0, 0);
const Color RGB_GREEN = Color(0, 255, 0);
const Color RGB_BLUE = Color(0, 0, 255);
const Color RGB_BLACK = Color(0, 0, 0);

const Color RGB_YELLOW = Color(255, 80, 0);
const Color RGB_PURPLE = Color(128, 0, 128);
const Color RGB_PINK = Color(255, 0, 255);
const Color RGB_LIGHTGREEN = Color(51, 204, 51);
const Color RGB_TURQUOISE = Color(64, 224, 208);

const Color COLOR_SCEPTICAL = Color(153, 5, 252);
const Color COLOR_INTERESTED = Color(244, 252, 5);
const Color COLOR_DISAPPOINTED = Color(153, 51, 51);
const Color COLOR_IMPRESSED = Color(233, 255, 0);
const Color COLOR_SURPRISED = RGB_GREEN;
const Color COLOR_ANGRY = RGB_RED;
const Color COLOR_ANXIOUS = RGB_YELLOW;//Color(165, 0, 255);
const Color COLOR_SUPPORTIVE = Color(29, 255, 0);
const Color COLOR_NORMAL = RGB_BLUE;

#endif