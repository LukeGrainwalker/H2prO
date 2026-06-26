#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

struct SequenceItem {
  int duration;
  void *data;
};

class Sequence {
public:
  Sequence(SequenceItem _items[], int len);
  Sequence(SequenceItem _items[], int len, bool loop);
  Sequence(SequenceItem _items[], int len, bool _loop, unsigned int pause);

  SequenceItem *getby_time(unsigned long time);
  void reset();

private:
  SequenceItem *items;

  int current_posistion;
  bool finished;
  bool loop;

  int length;
  unsigned long last_time;
  unsigned int pause_between;
};

#endif