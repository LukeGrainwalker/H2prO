#ifndef ACTION_HPP
#define ACTION_HPP

#include <Arduino.h>
#include "H2prO.hpp"

class Buzzer {};

class Action {
public:
  int process_emotion(enum emotion);
};

#endif