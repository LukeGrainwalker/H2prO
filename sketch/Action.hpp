#ifndef ACTION_HPP
#define ACTION_HPP

#include <Arduino.h>
#include "H2prO.hpp"
#include "LED.hpp"
#include "Sequence.hpp"

class Action {
private:
  enum emotion last;
public:
  int process_emotion(enum emotion);
};

#endif