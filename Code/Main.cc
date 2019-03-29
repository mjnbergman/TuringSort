/*
 * Main.cc
 *
 *  Created on: 26 Feb 2019
 *      Author: 20174570
 */

#include <iostream>
#include <thread>
#include "System.hh"
#include "SequenceInterpreter.hh"
#include "wiringPi.h"

System* GLOBAL_SYSTEM;
SequenceInterpreter *INTERPRETER;
int REQUEST_DONE = 0;
int FIBONACCI_B0 = 0;
int FIBONACCI_B1 = 0;
int FIBONACCI_B0_COUNT = 0;
int FIBONACCI_B1_COUNT = 0;
bool FIBONACCI_FILLING_B0 = true;


const double MOTOR_HOLD_DURATION = 200; // ms
const double BUCKET_DURATION_ZERO = 1000;
const double BUCKET_DURATION_ONE = 1000;
const double BUCKET_DURATION_TWO = 1000;
const double BUCKET_DURATION_THREE = 1000;
const int WASTE_BUCKET = 3;

int main(){

	  dzn::locator locator;
	  dzn::runtime runtime;
	  dzn::illegal_handler illegal_handler;

//	  wiringPiSetup();



	  int dataPin = 5, latchPin = 6, clockPin = 7;


	  System s(locator.set(runtime).set(illegal_handler));

	  GLOBAL_SYSTEM = &s;
	  INTERPRETER = new SequenceInterpreter();

	  s.sensor.sensor.port_turnOn();


	  auto timerLambda = [] (System s, double ms) {
		  	  auto executionLamba = [] {

		  	  };
			  TimerHelper t(s.pusherSystem.p1.timer.out.timeout);
	  };

    s.belt.control.motor.in.turnClockwise = [] {
        turnMotor(0, false);
    };

    s.belt.control.motor.in.turnCounterClockwise = [] {
        turnMotor(0, true);
    };

    s.belt.control.motor.in.off = [] {
        stopMotor(0);
    };

	  s.pusherSystem.p1.motor.in.turnClockwise = [] {
			  // Draai motor 1
        turnMotor(1, false);
	  };

	  s.pusherSystem.p2.motor.in.turnClockwise = [] {
			  // Draai motor 2
        turnMotor(2, false);
	  };

	  s.pusherSystem.p3.motor.in.turnClockwise = [] {
			  // Draai motor 3
        turnMotor(3, false);
	  };

    s.pusherSystem.p1.motor.in.turnCounterClockwise = [] {
        turnMotor(1, true);
    };

    s.pusherSystem.p2.motor.in.turnCounterClockwise = [] {
        turnMotor(2, true);
    };

    s.pusherSystem.p3.motor.in.turnCounterClockwise = [] {
        turnMotor(3, true);
    };

    s.pusherSystem.p1.motor.in.off = [] {
        stopMotor(1);
    };

    s.pusherSystem.p2.motor.in.off = [] {
        stopMotor(2);
    };

    s.pusherSystem.p3.motor.in.off = [] {
        stopMotor(3);
    };

	  s.pusherSystem.port.in.enqueueBox1 = [] (double ms){
		  auto upDownDelayLambda = [] (){
			  GLOBAL_SYSTEM->pusherSystem.p1.port.in.down();
			  GLOBAL_SYSTEM->pusherSystem.p2.port.in.up();
			  GLOBAL_SYSTEM->pusherSystem.p3.port.in.up();
		  };
		  TimerHelper t1(upDownDelayLambda);
		  int test = ms;
		  std::chrono::milliseconds ms1(test);
	      t1.start(ms1);
	  };

	  s.pusherSystem.port.in.enqueueBox2 = [] (double ms){
		  auto upDownDelayLambda = [] (){
			  GLOBAL_SYSTEM->pusherSystem.p1.port.in.up();
			  GLOBAL_SYSTEM->pusherSystem.p2.port.in.down();
			  GLOBAL_SYSTEM->pusherSystem.p3.port.in.up();
		  };
		  TimerHelper t1(upDownDelayLambda);
		  int test = ms;
		  std::chrono::milliseconds ms1(test);
	      t1.start(ms1);
	  };

	  s.pusherSystem.port.in.enqueueBox3 = [] (double ms){
		  auto upDownDelayLambda = [] (){
			  GLOBAL_SYSTEM->pusherSystem.p1.port.in.up();
			  GLOBAL_SYSTEM->pusherSystem.p2.port.in.up();
			  GLOBAL_SYSTEM->pusherSystem.p3.port.in.down();
		  };
		  TimerHelper t1(upDownDelayLambda);
		  int test = ms;
		  std::chrono::milliseconds ms1(test);
	      t1.start(ms1);
	  };
	  s.pusherSystem.port.in.enqueueBox4 = [] (double ms){
		  auto upDownDelayLambda = [] (){
			  GLOBAL_SYSTEM->pusherSystem.p1.port.in.up();
			  GLOBAL_SYSTEM->pusherSystem.p2.port.in.up();
			  GLOBAL_SYSTEM->pusherSystem.p3.port.in.up();
		  };
		  TimerHelper t1(upDownDelayLambda);
		  int test = ms;
		  std::chrono::milliseconds ms1(test);
	      t1.start(ms1);
	  };

	  s.app.sensor.out.measuresBlack = [] {
		  if (s.app.mode != SortingApplication::OperationMode::type::Rebooting && s.app.mode != SortingApplication::OperationMode::type::SequenceReading) {
			  Sequence *seq = INTERPRETER->getSequence();
			  SortingApplication::OperationMode::type type = seq->getMode();
			  if (type == SortingApplication::OperationMode::type::Sort) {
				  SortSequence *sort = dynamic_cast<SortSequence *>(&seq);
				  int bucket = sort->getBB();
				  enqueue(bucket);
			  } else if (type == SortingApplication::OperationMode::type::Request) {
				  RequestSequence *req = dynamic_cast<RequestSequence *>(&seq);
				  if (req->isWhite()) {
					  enqueue(WASTE_BUCKET);
				  } else {
					  int bucket = req->getContainer();
					  enqueue(bucket);
					  int a = req->getAmount();
					  REQUEST_DONE++;
					  if (a == REQUEST_DONE) {
						  INTERPRETER->cancel();
						  REQUEST_DONE = 0;
					  }
				  }
			  }
		  }
	  };

	  s.app.sensor.out.measuresWhite = [] {
			  if (s.app.mode != SortingApplication::OperationMode::type::Rebooting && s.app.mode != SortingApplication::OperationMode::type::SequenceReading) {
	  			  Sequence *seq = INTERPRETER->getSequence();
	  			  SortingApplication::OperationMode::type type = seq->getMode();
	  			  if (type == SortingApplication::OperationMode::type::Sort) {
	  				  SortSequence *sort = dynamic_cast<SortSequence *>(&seq);
	  				  int bucket = sort->getBW();
	  				  enqueue(bucket);
	  			  } else if (type == SortingApplication::OperationMode::type::Request) {
					  RequestSequence *req = dynamic_cast<RequestSequence *>(&seq);
					  if (req->isWhite()) {
						  int bucket = req->getContainer();
						  enqueue(bucket);
						  int a = req->getAmount();
						  REQUEST_DONE++;
						  if (a == REQUEST_DONE) {
						  	INTERPRETER->cancel();
						  	REQUEST_DONE = 0;
						  }
					  } else {
						  enqueue(WASTE_BUCKET);
					  }
				  } else if (type == SortingApplication::OperationMode::type::Fibonacci) {
					  FibonacciSequence *fib = dynamic_cast<FibonacciSequence *>(&seq);
					  int n = fib->getN();
					  int f = FibonacciSequence::getFibonacci(n);
					  if (f > FIBONACCI_B0_COUNT && FIBONACCI_FILLING_B0) {
						  enqueue(0);
						  FIBONACCI_B0_COUNT++;
						  int F = FibonacciSequence::getFibonacci(FIBONACCI_B0);
						  if (F == FIBONACCI_B0_COUNT){
							  if (F == f) {
								  //done, back to sorting mode;
								  std::cout << "FINISHED FIBONACCI(" + std::to_string(n) + ") = " + std::to_string(f) + "IN BUCKET 0" << std::endl;
								  INTERPRETER->cancel();
							  } else {
								  FIBONACCI_B1 += 2;
								  FIBONACCI_FILLING_B0 = !FIBONACCI_FILLING_B0;
							  }
						  }
					  } else if (f > FIBONACCI_B1_COUNT && !FIBONACCI_FILLING_B0) {
						  enqueue(1);
						  FIBONACCI_B1_COUNT++;
						  int F = FibonacciSequence::getFibonacci(FIBONACCI_B0);
						  if (F == FIBONACCI_B1_COUNT){
							  if (F == f) {
								  //done, back to sorting mode;
								  std::cout << "FINISHED FIBONACCI(" + std::to_string(n) + ") = " + std::to_string(f) + "IN BUCKET 1" << std::endl;
								  INTERPRETER->cancel();
							  } else {
								  FIBONACCI_B0 += 2;
								  FIBONACCI_FILLING_B0 = !FIBONACCI_FILLING_B0;
							  }
						  }
					  } else {
						  std::cout << "Whoops, Fibonacci weirdness" << std::endl;
					  }
				  }
	  		  }
	  	  };

	  while(true){
	  }

	return 0;
}

void enqueue(int bucket) {
	if (bucket == 0) {
		GLOBAL_SYSTEM->pusherSystem.port.in.enqueueBox1(BUCKET_DURATION_ZERO);
	} else if (bucket == 1) {
		GLOBAL_SYSTEM->pusherSystem.port.in.enqueueBox2(BUCKET_DURATION_ONE);
	} else if (bucket == 2) {
		GLOBAL_SYSTEM->pusherSystem.port.in.enqueueBox3(BUCKET_DURATION_TWO);
	} else if (bucket == 3) {
		GLOBAL_SYSTEM->pusherSystem.port.in.enqueueBox4(BUCKET_DURATION_THREE);
	}
}
