#ifndef ACTION_HPP
#define ACTION_HPP

#include <Arduino.h>
#include "H2prO.hpp"
#include "LED.hpp"

class Action {
public:
  int process_emotion(enum emotion);
};

#endif