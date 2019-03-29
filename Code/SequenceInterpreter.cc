

#include "SequenceInterpreter.hh";

SequenceInterpreter::SequenceInterpreter()
{
  counter = 0;
}

bool SequenceInterpreter::append(bool isWhite) {
  if (counter < 8) {
    array[counter] = isWhite;
    counter++;
  }
  if (counter >= 8) {
    readSequence(array);
    return true;
  }
  return false;
}

void SequenceInterpreter::cancel() {
  counter = 0;
}

void SequenceInterpreter::start() {
  counter = 0;
}

Sequence SequenceInterpreter::getSequence() {
  return seq;
}

void readSequence(bool[] sequence) {
  //sort operation
  if (!sequence[0] && !sequence[1]) {
    blackContainer = sequence[2] + sequence[3]*2;
    whiteContainer = sequence[4] + sequence[5]*2;
    seq = new  SortSequence(whiteContainer, blackContainer);
  }
  //request operation
  else if (!sequence[0] && sequence[1]) {
    container = sequence[2] + sequence[3]*2;
    white = sequence[4];
    amount = sequence[5] + sequence[6]*2 + sequence[7]*4 + 1;
    seq = new RequestSequence(container, white, amount);
  }
  //fibonacci operation
  else if(sequence[0] && !sequence[1]) {
    amount = sequence[2] + sequence[3]*2 + sequence[4]*4 + 1;
    seq = new FibonacciSequence(amount);
  }
}
