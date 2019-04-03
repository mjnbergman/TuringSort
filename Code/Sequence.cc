/*
 * Sequence.cc
 *
 *  Created on: 27 Mar 2019
 *      Author: Jari Martens
 */

#include "Sequence.hh"

Sequence::Sequence()
{
}

SortingApplication::OperationMode::type Sequence::getMode() const {
    return _mode;
}

SortSequence::SortSequence(int bw, int bb)
:_bw(bw), _bb(bb)
{
	this->_mode = ::SortingApplication::OperationMode::type::Sort;
}

int SortSequence::getBB() const {
    return _bb;
}

int SortSequence::getBW() const {
    return _bw;
}

RequestSequence::RequestSequence(int c, bool i, int a)
: _container(c), _isWhite(i), _amount(a)
{
	this->_mode = ::SortingApplication::OperationMode::type::Request;
}

int RequestSequence::getContainer() const {
    return _container;
}

bool RequestSequence::isWhite() const {
    return _isWhite;
}

int RequestSequence::getAmount() const {
    return _amount;
}

FibonacciSequence::FibonacciSequence(int n)
: _n(n)
{
	this->_mode = ::SortingApplication::OperationMode::Fibonacci;
}

int FibonacciSequence::getN() const {
    return _n;
}

/* Returns for 0 <= n < 8 a Fibonacci integer */
int FibonacciSequence::getFibonacci(int n) {
	if (n >= 8 || n < 0) {
		std::cerr << "Fibonacci requested for wrong index." << std::endl
				<< "Expected 0 <= n < 8, got n = " + std::to_string(n) << std::endl;
		return -1;
	} else if (n <= 1) {
		return 1;
	}
	return FibonacciSequence::getFibonacci(n-1) + FibonacciSequence::getFibonacci(n-2);
}
