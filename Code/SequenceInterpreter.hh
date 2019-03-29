#include "Sequence.hh";

class SequenceInterpreter {
public:
  SequenceInterpreter();
  bool append(bool isWhite);
  void cancel();
  void start();
  Sequence getSequence();

private:
  int counter;
  bool[8] array;
  Sequence seq;

  int operation;
  int blackContainer;
  int whiteContainer;
  int container;
  int amount;
  bool white;
}
