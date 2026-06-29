#ifndef SEQUENCES_HPP
#define SEQUENCES_HPP

#include "Sequence.hpp"
#include "colors.hpp"
#include "pitches.h"

enum SEQUENCE_NAME {
    SEQUENCE_ALARM = 0,
    SEQUENCE_DRINK,
    SEQUENCE_DISAPP,
    SEQUENCE_ANXIOUS_SOUND,
    SEQUENCE_SURPRISED_SOUND,
    SEQUENCE_IMPRESSED_SOUND,
    SEQUENCE_MAX
};

/* SequenceItem alarm_tones2[] = {
  {250, (void*)&NOTE_G5},
  {250, (void*)&NOTE_GS5},
  {500, (void*)&NOTE_A5},
  {250, (void*)&NOTE_AS5},
  {250, (void*)&NOTE_B5},
  {500, (void*)&NOTE_AS5},
  {125, (void*)&NOTE_C6},
  {1000, (void*)&NOTE_PAUSE}
}; */

#endif