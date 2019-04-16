#include "Sequence.hh";

class SequenceInterpreter {
public:
  SequenceInterpreter();
  bool append(bool isWhite);
  void cancel();
  void start();
  Sequence *getSequence();

private:
  int counter;
  bool array[8];
  Sequence* seq;

  void readSequence(bool sequence[]);
};
