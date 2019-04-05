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
#include <cstring>
#include "SequenceInterpreter.hh"
#include "MosquitoHandler.hh"
#include "LDRSensor.hh"
#include "SensorHelper.hh"
#include "QueueElement.hh"

#define yeet std::cout
#define YEET std::endl;

// Comment to force recompile
int p = 1;

// A global reference to the Dezyne System, needed to reference the Dezyne system in lambdas.
System* GLOBAL_SYSTEM;

// A reference to a SequenceInterpreter object.
SequenceInterpreter *INTERPRETER;



LDRSensor *SENSOR;

SensorHelper *S1;

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
const double MOTOR_BETWEEN_DELAY = 500;
const double SENSOR_TO_MOTOR1 = 900;
const double SENSOR_TO_MOTOR2 = 2250;
const double SENSOR_TO_MOTOR3 = 3200; // all in ms
const double SENSOR_TO_MOTOR4 = 4800;

// The protocol details of the MQTT host
char* MQTT_HOST = "tcp://192.168.0.2";
const int MQTT_PORT = 1883;
const int MQTT_KEEP_ALIVE = 60;

// A pre-declaration of the enqueue function.
void enqueue(int bucket);

const int WASTE_BUCKET = 3;
// The queue that motor-turn requests are placed in when calling enqueueBox1...enqueueBox4.
std::priority_queue <QueueElement, vector<QueueElement>, QueueCompare > boxQueue;

auto activateMotor1LambdaDown = [] () {
		GLOBAL_SYSTEM->pusherSystem.p1.port.in.down();
};
auto activateMotor2LambdaDown = [] () {
		GLOBAL_SYSTEM->pusherSystem.p2.port.in.down();
};
auto activateMotor3LambdaDown = [] () {
		GLOBAL_SYSTEM->pusherSystem.p3.port.in.down();
};
auto activateMotor1LambdaUp = [] () {
		GLOBAL_SYSTEM->pusherSystem.p1.port.in.up();
};
auto activateMotor2LambdaUp = [] () {
		GLOBAL_SYSTEM->pusherSystem.p2.port.in.up();
};
auto activateMotor3LambdaUp = [] () {
		GLOBAL_SYSTEM->pusherSystem.p3.port.in.up();
};

// A mutex used for locking the enqueueBox1...enqueueBox4 function lambdas.
std::mutex enqueu1Locker;

int main(int argc, char **argv){



	  // Dezyne initialization.
	  dzn::locator locator;
	  dzn::runtime runtime;
	  dzn::illegal_handler illegal_handler;


	  std::cout << "WiringPi? :)" << std::endl;
	  // Setup wiring pi.
	  wiringPiSetup();
	  std::cout << "WiringPi!!!" << std::endl;


	  // Initialize the main Dezyne System component.
	  System s(locator.set(runtime).set(illegal_handler));

	  std::cout << "En system!!!" << std::endl;

	  // Initialize MQTT
	  mqtt_setSystem(&s);
	  mqtt_init();

	  std::cout << "MQTT Initialized..." << std::endl;

	  TimerHelper mqtt_Threader([](){
		  std::cout << "In the lambda, before connecting to MQTT..." << " met host: " << MQTT_HOST << std::endl;
		  mqtt_connect(MQTT_HOST, MQTT_PORT, MQTT_KEEP_ALIVE);
		  std::cout << "Past connecting..." << std::endl;
		  mqtt_loopStart();
		  std::cout << "Somehow after the loop..." << std::endl;
	  });

	  mqtt_Threader.setDelay(100);
	  std::cout << "Before starting MQTT thread..." << std::endl;
	  mqtt_Threader.start();

	  // Set references to the global system and SequenceInterpreter
	  GLOBAL_SYSTEM = &s;
	  INTERPRETER = new SequenceInterpreter();


	  char* startSequence;

	  if(argc > 1){
		 std::cout << "Pre interpreter start..." << std::endl;
		 INTERPRETER->start();
	     startSequence = argv[1];
	     std::cout << "Er zijn: " << std::strlen(argv[1]) << " argumenten!" << std::endl;
	     for(int i = 0; i < std::strlen(argv[1]); i++){
	    	 bool whiteOrBlack = argv[1][i] - 48 == 0 ? false : true;
	    	 INTERPRETER->append(whiteOrBlack);
	    	 std::cout << "Appending a chip..." << whiteOrBlack << std::endl;
	      }
	  }if(argc > 2){
		  MQTT_HOST = argv[2];
	  }

	//  delay(100000);


/*
	  INTERPRETER->append(false);
	  INTERPRETER->append(false);
	  INTERPRETER->append(false);
	  INTERPRETER->append(false);
	  INTERPRETER->append(true);
	  INTERPRETER->append(false);
	  INTERPRETER->append(false);
	  INTERPRETER->append(false);
*/

	  auto callbackError = [] () {
		  std::cout << "Measures error\n";
		  GLOBAL_SYSTEM->app.sensor.out.measuresError();
	  };

	  auto callbackWhite = [] () {
		  std::cout << "Measures white\n";
		  GLOBAL_SYSTEM->app.sensor.out.measuresWhite();
	  };

	  auto callbackBlack = [] () {
		  std::cout << "Measures black\n";
		  GLOBAL_SYSTEM->app.sensor.out.measuresBlack();
	  };

	// Sensor initialization
	  SENSOR = new LDRSensor(callbackError, callbackWhite, callbackBlack);
	  SENSOR->sensorSetup();

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

    s.port.in.startSequence = [] () {
    	INTERPRETER->start();
    };

    // MQTT lambdas
    s.port.out.available = [] () {
    	std::cout << "In lambda MQTT Available call..." << std::endl;
    	mqtt_available();
    };

    s.port.out.sequenceReceived = [] () {
    	  std::cout << "In lambda MQTT sequenceReceived() call..." << std::endl;
        mqtt_sequenceReceived();
    };

    s.port.out.sendEmergency = [] () {
    	  std::cout << "In lambda MQTT sendEmergency() call..." << std::endl;
        mqtt_sendEmergency();
    };

    s.port.in.reboot = [] () {
   	 GLOBAL_SYSTEM->pusherSystem.m1.port_turnCounterClockwise();
   	 GLOBAL_SYSTEM->pusherSystem.m2.port_turnCounterClockwise();
   	 GLOBAL_SYSTEM->pusherSystem.m3.port_turnCounterClockwise();
   	 delay(500);
    };




    // enqueueBox1...enqueueBox4 motor lambdas.
	  s.pusherSystem.port.in.enqueueBox1 = [] (double ms){

	//	  GLOBAL_SYSTEM->pusherSystem.p1.port.in.down();
	//	  GLOBAL_SYSTEM->pusherSystem.p2.port.in.up();
	//	  GLOBAL_SYSTEM->pusherSystem.p3.port.in.up();




		  TimerHelper* t1 = new TimerHelper(activateMotor1LambdaDown);

//		  t1->setDelay(SENSOR_TO_MOTOR1);
		  QueueElement qe;
		  qe.th = t1;
		  qe.timeStamp = SENSOR_TO_MOTOR1 + millis();
		  boxQueue.push(qe);

		  std::cout << "De timestamp is: " << qe.timeStamp << " en het is nu: " << millis() << std::endl;
		  //std::cout << "Test enqueue..." << std::endl;
	  };

	  s.pusherSystem.port.in.enqueueBox2 = [] (double ms){

//			  GLOBAL_SYSTEM->pusherSystem.p1.port.in.up();
//			  GLOBAL_SYSTEM->pusherSystem.p2.port.in.down();
//			  GLOBAL_SYSTEM->pusherSystem.p3.port.in.up();
//			  enqueu1Locker.unlock();

			  TimerHelper* t1 = new TimerHelper(activateMotor1LambdaUp);
			  TimerHelper* t2 = new TimerHelper(activateMotor2LambdaDown);

			  QueueElement qe;
			  qe.th = t1;
			  qe.timeStamp = SENSOR_TO_MOTOR1 + millis();
			  boxQueue.push(qe);
			  QueueElement qe2;
			  qe2.th = t2;
			  qe2.timeStamp = SENSOR_TO_MOTOR2 + millis();
			  boxQueue.push(qe2);
	  };

	  s.pusherSystem.port.in.enqueueBox3 = [] (double ms){

//			  GLOBAL_SYSTEM->pusherSystem.p1.port.in.up();
//			  GLOBAL_SYSTEM->pusherSystem.p2.port.in.up();
//			  GLOBAL_SYSTEM->pusherSystem.p3.port.in.down();
//			  enqueu1Locker.unlock();
			  TimerHelper* t1 = new TimerHelper(activateMotor1LambdaUp);
			  TimerHelper* t2 = new TimerHelper(activateMotor2LambdaUp);
			  TimerHelper* t3 = new TimerHelper(activateMotor3LambdaDown);

			  QueueElement qe;
			  qe.th = t1;
			  qe.timeStamp = SENSOR_TO_MOTOR1 + millis();
			  boxQueue.push(qe);
			  QueueElement qe2;
			  qe2.th = t2;
			  qe2.timeStamp = SENSOR_TO_MOTOR2 + millis();
			  boxQueue.push(qe2);
			  QueueElement qe3;
			  qe3.th = t3;
			  qe3.timeStamp = SENSOR_TO_MOTOR3 + millis();
			  boxQueue.push(qe3);
	  };
	  s.pusherSystem.port.in.enqueueBox4 = [] (double ms){

//			  GLOBAL_SYSTEM->pusherSystem.p1.port.in.up();
//			  GLOBAL_SYSTEM->pusherSystem.p2.port.in.up();
//			  GLOBAL_SYSTEM->pusherSystem.p3.port.in.up();

		  TimerHelper* t1 = new TimerHelper(activateMotor1LambdaUp);
		  TimerHelper* t2 = new TimerHelper(activateMotor2LambdaUp);
		  TimerHelper* t3 = new TimerHelper(activateMotor3LambdaUp);

		  QueueElement qe;
		  qe.th = t1;
		  qe.timeStamp = SENSOR_TO_MOTOR1 + millis();
		  boxQueue.push(qe);
		  QueueElement qe2;
		  qe2.th = t2;
		  qe2.timeStamp = SENSOR_TO_MOTOR2 + millis();
		  boxQueue.push(qe2);
		  QueueElement qe3;
		  qe3.th = t3;
		  qe3.timeStamp = SENSOR_TO_MOTOR3 + millis();
		  boxQueue.push(qe3);
	  };

	  s.app.sensor.in.turnOn = [] (){
		  auto loopFunc = [] () {
			  SENSOR->sensorLoop();
		  };
	//	  SENSOR->sensorSetup();
		  SENSOR->calibrate();
		  S1 = new SensorHelper(loopFunc);
		  S1->start();
	  };

	  s.app.sensor.in.calibrate = [] () {
	  };

	  s.app.sensor.in.turnOff = [] () {
		  S1->stop();
	  };

	  s.sequence.port.in.appendBlack = [] () {
		  bool done = INTERPRETER->append(false);
		  if (done) {
			  GLOBAL_SYSTEM->sequence.port.out.readSequence();
		  }
	  };

	  s.sequence.port.in.appendWhite = [] () {
		  bool done = INTERPRETER->append(true);
		  if (done) {
			  GLOBAL_SYSTEM->sequence.port.out.readSequence();
		  }
	  };

	  s.sequence.port.in.startSequence = [] () {
		  INTERPRETER->start();
	  };

	  s.sequence.port.in.cancelSequence = [] () {
		  INTERPRETER->cancel();
	  };
  
	  // Sensor lambdas
	  s.app.sensor.out.measuresBlack = [] {
		  std::cout << "MEASURES BLACK!!!!\n\n\n";
		  if (GLOBAL_SYSTEM->app.mode != SortingApplication::OperationMode::type::Rebooting && GLOBAL_SYSTEM->app.mode != SortingApplication::OperationMode::type::SequenceReading) {
			  Sequence *seq = INTERPRETER->getSequence();
			  SortingApplication::OperationMode::type type = seq->getMode();
			  if (type == SortingApplication::OperationMode::type::Sort) {
				  SortSequence *sort = dynamic_cast<SortSequence *>(seq);
				  int bucket = sort->getBB();
				  enqueue(bucket);
				  std::cout << "Found a black chip!!! Enqueueing in bucket: " << bucket << std::endl;
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
				  yeet << "Measured black and in fibonacci" << YEET;
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
			  std::cout << "MEASURES WHITE!!!\n\n\n";
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
					  yeet << "Measured white and entering fibonacci" << YEET;
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

	 s.app.sensor.in.turnOn();
	 s.pusherSystem.m1.port_turnCounterClockwise();
	 s.pusherSystem.m2.port_turnCounterClockwise();
	 s.pusherSystem.m3.port_turnCounterClockwise();

	 delay(500);

  	 std::cout << "Before belt en ik leef";
     s.belt.port.in.setCounterClockwise();
  	 // Turn on the conveyer belt, this should always be running
	  s.belt.port.in.turnOn();
//	  s.pusherSystem.m1.turnMotor(true);
//	  GLOBAL_SYSTEM->pusherSystem.p1.port.in.up();
//	  s.pusherSystem.p2.port.in.up();
//	  GLOBAL_SYSTEM->pusherSystem.p3.port.in.up();
	  std::cout << " \n after belt en ik leef";
	//  delay(1000);
	//  s.pusherSystem.port.in.enqueueBox1(SENSOR_TO_MOTOR1);
	//  s.pusherSystem.port.in.enqueueBox2(SENSOR_TO_MOTOR2);
	//  s.pusherSystem.port.in.enqueueBox3(SENSOR_TO_MOTOR3);
	//  s.pusherSystem.port.in.enqueueBox4(SENSOR_TO_MOTOR4);

	  // A permanent loop so the system will always continue running unless the power is taken off
	  // or the execution of the application terminated.
	  while(true){
		//  std::cout << " Test loop! ";
		//  std::cout << "Het komt voorbij de eerste enqueue ronde!" << std::endl;

		  // Pop the top element from the queue (a request to put a chip in a certain box) and execute
		  // that request (so move the motors to such a position that a chip passing by will land
		  // in the corresponding box.

		  if(!boxQueue.empty()){
			  std::cout << "De queue is niet empty, dequeue de top..." << std::endl;
			  QueueElement curQueue = boxQueue.top();
			  curQueue.th->setDelay(curQueue.timeStamp - millis());
			  std::cout << "De delay is: " << curQueue.th->getDelay().count() << std::endl;
			  curQueue.th->start();
			  boxQueue.pop();
		  }
//		  delay(MOTOR_BETWEEN_DELAY);

		 // std::cout << "Het komt voorbij de eerste enqueue execution!" << std::endl;
	  }

	  // Do some MQTT cleanup
    mqtt_cleanup();
	return 0;
}

// The enqueue function, just a wrapper for the specific enqueueBox1...enqueueBox4 calls allowing you to
// pick one of them based on the box number programmatically.
void enqueue(int bucket) {
	std::cout << "Enqueuing to bucket: " << bucket << std::endl;
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
