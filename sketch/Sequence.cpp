#include "Sequence.hpp"

Sequence::Sequence(SequenceItem _items[]) {
  items = _items;
  finished = false;
  pause_between = 0;
}

Sequence::Sequence(SequenceItem _items[], bool _loop) : Sequence(_items) {
  loop = _loop;
}

Sequence::Sequence(SequenceItem _items[], bool _loop, unsigned int pause)
    : Sequence(_items, _loop) {

  pause_between = pause;
}

void Sequence::reset() {
  current_posistion = 0;
  finished = false;
}

SequenceItem *Sequence::getby_time(unsigned long time) {

  if (finished && !loop) {
    return nullptr;
  }

  unsigned int time_passed = time - last_time;
  bool do_next_tone =
      time_passed > items[current_posistion].duration + pause_between;

  if (do_next_tone) {
    if (!finished) {
      current_posistion++;
    } else {
      reset();
    }

    last_time = time;
  }
  
  SequenceItem *current_item = &items[current_posistion];
  if (current_item->last) {
    finished = true;
  }

  return current_item;
}