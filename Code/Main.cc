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

System* GLOBAL_SYSTEM;

const int dataPin = 12, latchPin = 13, clockPin = 14;

const double MOTOR_HOLD_DURATION = 200; // ms

int main(){

	  dzn::locator locator;
	  dzn::runtime runtime;
	  dzn::illegal_handler illegal_handler;

	  wiringPiSetup();

	  System s(locator.set(runtime).set(illegal_handler));

	  GLOBAL_SYSTEM = &s;

//	  s.sensor.sensor.port_turnOn();


	  auto timerLambda = [] (System s, double ms) {
		  	  auto executionLamba = [] {

		  	  };
			  TimerHelper t(s.pusherSystem.p1.timer.out.timeout);
	  };

    s.belt.motor.setMotorNumber(0);
    s.belt.motor.setPins(dataPin, latchPin, clockPin);



    s.pusherSystem.m1.setMotorNumber(1);
    s.pusherSystem.m1.setPins(dataPin, latchPin, clockPin);

    s.pusherSystem.m2.setMotorNumber(2);
    s.pusherSystem.m2.setPins(dataPin, latchPin, clockPin);

    s.pusherSystem.m3.setMotorNumber(3);
    s.pusherSystem.m3.setPins(dataPin, latchPin, clockPin);

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

	  std::cout << "Before belt en ik leef";

	  //s.belt.port.in.turnOn();
	  s.belt.motor.turnMotor(true);

	  std::cout << " \n after belt en ik leef";
	  delay(20000);
	  while(true){
		  std::cout << " Test loop! ";
		  delay(500);
		  s.pusherSystem.port.in.enqueueBox1(200);
		  std::cout << "Enqueue 1" << std::endl;
		  delay(500);
		  s.pusherSystem.port.in.enqueueBox2(200);
		  delay(500);
		  s.pusherSystem.port.in.enqueueBox3(200);
		  delay(500);
		  s.pusherSystem.port.in.enqueueBox4(200);
		  delay(500);
	  }

	return 0;
}
