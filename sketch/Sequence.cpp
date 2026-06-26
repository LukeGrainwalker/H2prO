#include "Sequence.hpp"

Sequence::Sequence(SequenceItem _items[], int len) {
  length = len;
  items = _items;
  finished = false;
  pause_between = 0;
}

Sequence::Sequence(SequenceItem _items[], int len, bool _loop)
    : Sequence(_items, len) {

  loop = _loop;
}

Sequence::Sequence(SequenceItem _items[], int len, bool _loop, unsigned int pause)
    : Sequence(_items, len, _loop) {

    pause_between = pause;
}

void Sequence::reset() {
    current_posistion = 0;
    finished = false;
}

SequenceItem *Sequence::getby_time(unsigned long time) {
  SequenceItem *current_item;

  if (current_posistion == (length - 1) && !loop || finished) {
    return nullptr;
  }

  unsigned int time_passed = time - last_time;
  bool do_next_tone = time_passed > items[current_posistion].duration + pause_between;

  if (do_next_tone) {
    if (!loop && (current_posistion + 1 == length)) {
      finished = true;
      return nullptr;
    }

    current_posistion = (current_posistion + 1) % length;
    current_item = &items[current_posistion];
    last_time = time;
  }

  current_item = &items[current_posistion];
  return current_item;
}