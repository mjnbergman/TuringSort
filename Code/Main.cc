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

std::queue<TimerHelper*> boxQueue;

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

    s.pusherSystem.p1.time = MOTOR_HOLD_DURATION;
    s.pusherSystem.p2.time = MOTOR_HOLD_DURATION;
    s.pusherSystem.p3.time = MOTOR_HOLD_DURATION;

	  s.pusherSystem.port.in.enqueueBox1 = [] (double ms){
		  auto upDownDelayLambda = [] (){
			  GLOBAL_SYSTEM->pusherSystem.p1.port.in.down();
			  GLOBAL_SYSTEM->pusherSystem.p2.port.in.up();
			  GLOBAL_SYSTEM->pusherSystem.p3.port.in.up();
		  };
		  TimerHelper t1(upDownDelayLambda);
		  t1.setDelay((int)ms);
		  boxQueue.push(&t1);
	  };

	  s.pusherSystem.port.in.enqueueBox2 = [] (double ms){
		  auto upDownDelayLambda = [] (){
			  GLOBAL_SYSTEM->pusherSystem.p1.port.in.up();
			  GLOBAL_SYSTEM->pusherSystem.p2.port.in.down();
			  GLOBAL_SYSTEM->pusherSystem.p3.port.in.up();
		  };
		  TimerHelper t1(upDownDelayLambda);
		  t1.setDelay((int)ms);
		  boxQueue.push(&t1);
	  };

	  s.pusherSystem.port.in.enqueueBox3 = [] (double ms){
		  auto upDownDelayLambda = [] (){
			  GLOBAL_SYSTEM->pusherSystem.p1.port.in.up();
			  GLOBAL_SYSTEM->pusherSystem.p2.port.in.up();
			  GLOBAL_SYSTEM->pusherSystem.p3.port.in.down();
		  };
		  TimerHelper t1(upDownDelayLambda);
		  t1.setDelay((int)ms);
		  boxQueue.push(&t1);
	  };
	  s.pusherSystem.port.in.enqueueBox4 = [] (double ms){
		  auto upDownDelayLambda = [] (){
			  GLOBAL_SYSTEM->pusherSystem.p1.port.in.up();
			  GLOBAL_SYSTEM->pusherSystem.p2.port.in.up();
			  GLOBAL_SYSTEM->pusherSystem.p3.port.in.up();
		  };
		  TimerHelper t1(upDownDelayLambda);
		  t1.setDelay((int)ms);
		  boxQueue.push(&t1);
	  };

	  std::cout << "Before belt en ik leef";

	  //s.belt.port.in.turnOn();
	  s.belt.motor.turnMotor(true);
//	  s.pusherSystem.m1.turnMotor(true);
//	  GLOBAL_SYSTEM->pusherSystem.p1.port.in.up();
//	  s.pusherSystem.p2.port.in.up();
//	  GLOBAL_SYSTEM->pusherSystem.p3.port.in.up();
	  std::cout << " \n after belt en ik leef";
	  delay(5000);
	  while(true){
		  std::cout << " Test loop! ";
		  delay(100);
		  s.pusherSystem.port.in.enqueueBox1(200);
		  std::cout << "Enqueue 1" << std::endl;
		  delay(100);
		  s.pusherSystem.port.in.enqueueBox2(200);
		  delay(100);
		  s.pusherSystem.port.in.enqueueBox3(200);
		  delay(100);
		  s.pusherSystem.port.in.enqueueBox4(200);
		  delay(100);

		  std::cout << "Het komt voorbij de eerste enqueue ronde!" << std::endl;

		  boxQueue.front()->start();
		  boxQueue.pop();

		  std::cout << "Het komt voorbij de eerste enqueue execution!" << std::endl;
	  }

	return 0;
}
