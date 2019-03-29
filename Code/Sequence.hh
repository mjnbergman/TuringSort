#include "System.hh"

#ifndef CODE_SEQUENCE_HH_
#define CODE_SEQUENCE_HH_

class Sequence {
protected:
    SortingApplication::OperationMode::type _mode;

public:
    Sequence();
    SortingApplication::OperationMode::type getMode() const;
};

class SortSequence: public Sequence {
private:
    int _bw;
    int _bb;
public:
    SortSequence(int bw, int bb);
    int getBB() const;
    int getBW() const;
};

class RequestSequence: public Sequence {
private:
    int _container;
    bool _isWhite;
    int _amount;
public:
    RequestSequence(int c, bool i, int a);
    int getContainer() const;
    bool isWhite() const;
    int getAmount() const;
};

class FibonacciSequence: public Sequence {
private:
    int _n;
public:
    FibonacciSequence(int n);
    int getN() const;
    static int getFibonacci(int n);
};

#endif /* CODE_SEQUENCE_HH_ */
