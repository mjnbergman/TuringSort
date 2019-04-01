/*
 * Main.cc
 *
 *  Created on: 26 Feb 2019
 *      Author: 20174570
 */

#include <iostream>
#include <thread>
#include "System.hh"
#include <wiringPi.h>
#include <mutex>
#include "SequenceInterpreter.hh"
#include "MosquitoHandler.hh"

// A global reference to the Dezyne System, needed to reference the Dezyne system in lambdas.
System* GLOBAL_SYSTEM;

// A reference to a SequenceInterpreter object.
SequenceInterpreter *INTERPRETER;

// Fibonacci globals
int REQUEST_DONE = 0;
int FIBONACCI_B0 = 0;
int FIBONACCI_B1 = 0;
int FIBONACCI_B0_COUNT = 0;
int FIBONACCI_B1_COUNT = 0;
bool FIBONACCI_FILLING_B0 = true;

// Define the shift register pins globally, these will be used for the motors.
const int dataPin = 12, latchPin = 13, clockPin = 14;

// Constant durations we measured and determined the values of experimentally, used
// to determine the amount of time timers should wait when activating motors and other things.
const double MOTOR_HOLD_DURATION = 200; // ms
const double SENSOR_TO_MOTOR1 = 1000;
const double SENSOR_TO_MOTOR2 = 1200;
const double SENSOR_TO_MOTOR3 = 1600; // all in ms
const double SENSOR_TO_MOTOR4 = 2000;

// The protocol details of the MQTT host
const char* MQTT_HOST = "tcp://192.168.0.2";
const int MQTT_PORT = 1883;
const int MQTT_KEEP_ALIVE = 60;

// A pre-declaration of the enqueue function.
void enqueue(int bucket);

const int WASTE_BUCKET = 3;

// The queue that motor-turn requests are placed in when calling enqueueBox1...enqueueBox4.
std::queue<TimerHelper*> boxQueue;

// A mutex used for locking the enqueueBox1...enqueueBox4 function lambdas.
std::mutex enqueu1Locker;

int main(){

	  // Dezyne initialization.
	  dzn::locator locator;
	  dzn::runtime runtime;
	  dzn::illegal_handler illegal_handler;


	  // Setup wiring pi.
	  wiringPiSetup();


	  // Initialize the main Dezyne System component.
	  System s(locator.set(runtime).set(illegal_handler));


	  // Initialize MQTT
	  mqtt_setSystem(&s);
	  mqtt_init();

	  TimerHelper mqtt_Threader([](){
		  mqtt_connect(MQTT_HOST, MQTT_PORT, MQTT_KEEP_ALIVE);
	  });

	  mqtt_Threader.setDelay(100);
	  mqtt_Threader.start();

	  // Set references to the global system and SequenceInterpreter
	  GLOBAL_SYSTEM = &s;
	  INTERPRETER = new SequenceInterpreter();

//	  s.sensor.sensor.port_turnOn();


	  auto timerLambda = [] (System s, double ms) {
		  	  auto executionLamba = [] {

		  	  };
			  TimerHelper t(s.pusherSystem.p1.timer.out.timeout);
	  };


	// Motor and conveyer belt initialization.
    s.belt.motor.setMotorNumber(0);
    s.belt.motor.setPins(dataPin, latchPin, clockPin);


    s.pusherSystem.m1.setMotorNumber(1);
    s.pusherSystem.m1.setPins(dataPin, latchPin, clockPin);

    s.pusherSystem.m2.setMotorNumber(2);
    s.pusherSystem.m2.setPins(dataPin, latchPin, clockPin);

    s.pusherSystem.m3.setMotorNumber(3);
    s.pusherSystem.m3.setPins(dataPin, latchPin, clockPin);

    s.pusherSystem.p1.time = MOTOR_HOLD_DURATION;
    s.pusherSystem.p2.time = MOTOR_HOLD_DURATION;
    s.pusherSystem.p3.time = MOTOR_HOLD_DURATION;

    // Timing constant initialization
    s.app.box1Time = SENSOR_TO_MOTOR1;
    s.app.box2Time = SENSOR_TO_MOTOR2;
    s.app.box3Time = SENSOR_TO_MOTOR3;
    s.app.box4Time = SENSOR_TO_MOTOR4;

    // MQTT lambdas
    s.port.out.available = [] () {
    	mqtt_available();
    };

    s.port.out.sequenceReceived = [] () {
        mqtt_sequenceReceived();
    };

    s.port.out.sendEmergency = [] () {
        mqtt_sendEmergency();
    };

    // enqueueBox1...enqueueBox4 motor lambdas.
	  s.pusherSystem.port.in.enqueueBox1 = [] (double ms){
		  auto upDownDelayLambda = [] (){
			// When this lambda is executed, move the motors in such a way that a chip passing through
			// will land in box 1.
			enqueu1Locker.lock();
			  std::cout << "Start van de lambda!!!" << std::endl;

			  GLOBAL_SYSTEM->pusherSystem.p1.port.in.down();
			  GLOBAL_SYSTEM->pusherSystem.p2.port.in.up();
			  GLOBAL_SYSTEM->pusherSystem.p3.port.in.up();
			  std::cout << "Done with executing enqueueBox1!!!" << std::endl;
			  enqueu1Locker.unlock();
			  //std::cout << "Test in de lambda" << std::endl;
		  };
		  TimerHelper* t1 = new TimerHelper(upDownDelayLambda);
		  t1->setDelay((int)ms);
		  boxQueue.push(t1);
		  //std::cout << "Test enqueue..." << std::endl;
	  };

	  s.pusherSystem.port.in.enqueueBox2 = [] (double ms){
		  auto upDownDelayLambda = [] (){
				// When this lambda is executed, move the motors in such a way that a chip passing through
				// will land in box 2.
			  enqueu1Locker.lock();
			  GLOBAL_SYSTEM->pusherSystem.p1.port.in.up();
			  GLOBAL_SYSTEM->pusherSystem.p2.port.in.down();
			  GLOBAL_SYSTEM->pusherSystem.p3.port.in.up();
			  enqueu1Locker.unlock();
		  };
		  TimerHelper* t1 = new TimerHelper(upDownDelayLambda);
		  t1->setDelay((int)ms);
		  boxQueue.push(t1);
	  };

	  s.pusherSystem.port.in.enqueueBox3 = [] (double ms){
		  auto upDownDelayLambda = [] (){
				// When this lambda is executed, move the motors in such a way that a chip passing through
				// will land in box 1.
			  enqueu1Locker.lock();
			  GLOBAL_SYSTEM->pusherSystem.p1.port.in.up();
			  GLOBAL_SYSTEM->pusherSystem.p2.port.in.up();
			  GLOBAL_SYSTEM->pusherSystem.p3.port.in.down();
			  enqueu1Locker.unlock();
		  };
		  TimerHelper* t1 = new TimerHelper(upDownDelayLambda);
		  t1->setDelay((int)ms);
		  boxQueue.push(t1);
	  };
	  s.pusherSystem.port.in.enqueueBox4 = [] (double ms){
		  auto upDownDelayLambda = [] (){
				// When this lambda is executed, move the motors in such a way that a chip passing through
				// will land in box 4.
			  enqueu1Locker.lock();
			  GLOBAL_SYSTEM->pusherSystem.p1.port.in.up();
			  GLOBAL_SYSTEM->pusherSystem.p2.port.in.up();
			  GLOBAL_SYSTEM->pusherSystem.p3.port.in.up();
			  enqueu1Locker.unlock();
		  };
		  TimerHelper* t1 = new TimerHelper(upDownDelayLambda);
		  t1->setDelay((int)ms);
		  boxQueue.push(t1);
	  };
  
	  // Sensor lambdas
	  s.app.sensor.out.measuresBlack = [] {
		  if (GLOBAL_SYSTEM->app.mode != SortingApplication::OperationMode::type::Rebooting && GLOBAL_SYSTEM->app.mode != SortingApplication::OperationMode::type::SequenceReading) {
			  Sequence *seq = INTERPRETER->getSequence();
			  SortingApplication::OperationMode::type type = seq->getMode();
			  if (type == SortingApplication::OperationMode::type::Sort) {
				  SortSequence *sort = dynamic_cast<SortSequence *>(seq);
				  int bucket = sort->getBB();
				  enqueue(bucket);
			  } else if (type == SortingApplication::OperationMode::type::Request) {
				  RequestSequence *req = dynamic_cast<RequestSequence *>(seq);
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
			  } else if (type == SortingApplication::OperationMode::type::Fibonacci) {
				  FibonacciSequence *fib = dynamic_cast<FibonacciSequence *>(seq);
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

	  s.app.sensor.out.measuresWhite = [] {
			  if (GLOBAL_SYSTEM->app.mode != SortingApplication::OperationMode::type::Rebooting && GLOBAL_SYSTEM->app.mode != SortingApplication::OperationMode::type::SequenceReading) {
	  			  Sequence *seq = INTERPRETER->getSequence();
	  			  SortingApplication::OperationMode::type type = seq->getMode();
	  			  if (type == SortingApplication::OperationMode::type::Sort) {
	  				  SortSequence *sort = dynamic_cast<SortSequence *>(seq);
	  				  int bucket = sort->getBW();
	  				  enqueue(bucket);
	  			  } else if (type == SortingApplication::OperationMode::type::Request) {
					  RequestSequence *req = dynamic_cast<RequestSequence *>(seq);
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
					  FibonacciSequence *fib = dynamic_cast<FibonacciSequence *>(seq);
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

  	 std::cout << "Before belt en ik leef";

  	 // Turn on the conveyer belt, this should always be running
	  s.belt.motor.turnMotor(true);
//	  s.pusherSystem.m1.turnMotor(true);
//	  GLOBAL_SYSTEM->pusherSystem.p1.port.in.up();
//	  s.pusherSystem.p2.port.in.up();
//	  GLOBAL_SYSTEM->pusherSystem.p3.port.in.up();
	  std::cout << " \n after belt en ik leef";
	  delay(1000);

	  // A permanent loop so the system will always continue running unless the power is taken off
	  // or the execution of the application terminated.
	  while(true){
		  std::cout << " Test loop! ";
		  delay(500);
		  s.pusherSystem.port.in.enqueueBox1(200);
		  std::cout << "Enqueue 1" << std::endl;
		  delay(500);
		  s.pusherSystem.port.in.enqueueBox2(200);
		  std::cout << "Enqueue 2" << std::endl;
		  delay(500);
		  s.pusherSystem.port.in.enqueueBox3(200);
		  std::cout << "Enqueue 3" << std::endl;
		  delay(500);
		  s.pusherSystem.port.in.enqueueBox4(200);
		  std::cout << "Enqueue 4" << std::endl;
		  delay(500);

		  std::cout << "Het komt voorbij de eerste enqueue ronde!" << std::endl;


		  // Pop the top element from the queue (a request to put a chip in a certain box) and execute
		  // that request (so move the motors to such a position that a chip passing by will land
		  // in the corresponding box.
		  boxQueue.front()->start();
		  boxQueue.pop();

		  std::cout << "Het komt voorbij de eerste enqueue execution!" << std::endl;
	  }

	  // Do some MQTT cleanup
	  mqtt_cleanup();
	return 0;
}

// The enqueue function, just a wrapper for the specific enqueueBox1...enqueueBox4 calls allowing you to
// pick one of them based on the box number programmatically.
void enqueue(int bucket) {
	if (bucket == 0) {
		GLOBAL_SYSTEM->pusherSystem.port.in.enqueueBox1(SENSOR_TO_MOTOR1);
	} else if (bucket == 1) {
		GLOBAL_SYSTEM->pusherSystem.port.in.enqueueBox2(SENSOR_TO_MOTOR2);
	} else if (bucket == 2) {
		GLOBAL_SYSTEM->pusherSystem.port.in.enqueueBox3(SENSOR_TO_MOTOR3);
	} else if (bucket == 3) {
		GLOBAL_SYSTEM->pusherSystem.port.in.enqueueBox4(SENSOR_TO_MOTOR4);
	}
}
