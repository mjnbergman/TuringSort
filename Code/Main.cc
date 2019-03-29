/*
 * Main.cc
 *
 *  Created on: 26 Feb 2019
 *      Author: 20174570
 */

#include <iostream>
#include <thread>
#include "System.hh"
#include "wiringPi.h"

using namespace std;

class TimerHelper
{
    thread th;
    bool running = false;
    std::function<void(void)> timeoutFunc;

public:
    typedef std::chrono::milliseconds Interval;
    typedef std::function<void(void)> Timeout;

    TimerHelper(Timeout timeoutFunc) : timeoutFunc(timeoutFunc){};

    void start(const Interval &interval)
    {
        running = true;

        th = thread([=]()
        {
            while (running == true) {
                this_thread::sleep_for(interval);
                this->timeoutFunc();
            }
        });

// [*]
        th.join();
    }

    void stop()
    {
        running = false;
    }
};

System* GLOBAL_SYSTEM;

const double MOTOR_HOLD_DURATION = 200; // ms

int main(){

	  dzn::locator locator;
	  dzn::runtime runtime;
	  dzn::illegal_handler illegal_handler;

//	  wiringPiSetup();



	  int dataPin = 5, latchPin = 6, clockPin = 7;


	  System s(locator.set(runtime).set(illegal_handler));

	  GLOBAL_SYSTEM = &s;

	  s.sensor.sensor.port_turnOn();


	  auto timerLambda = [] (System s, double ms) {
		  	  auto executionLamba = [] {

		  	  };
			  TimerHelper t(s.pusherSystem.p1.timer.out.timeout);
	  };

	  s.pusherSystem.p1.motor.in.turnClockwise = [] {
			  // Draai motor 1
	  };

	  s.pusherSystem.p2.motor.in.turnClockwise = [] {
			  // Draai motor 2
	  };

	  s.pusherSystem.p3.motor.in.turnClockwise = [] {
			  // Draai motor 3
	  };

	  s.pusherSystem.p1.timer.in.createTimer = [] (double time) {
		  TimerHelper t(GLOBAL_SYSTEM->pusherSystem.p1.timer.out.timeout);
		 // int ms = time;
		 // std::chrono::duration<int, std::milli>;
		  int test = time;
		  std::chrono::milliseconds ms(test);
		  t.start(ms);
	  };
	  s.pusherSystem.p2.timer.in.createTimer = [] (double time) {
		  TimerHelper t(GLOBAL_SYSTEM->pusherSystem.p2.timer.out.timeout);
		 // int ms = time;
		 // std::chrono::duration<int, std::milli>;
		  int test = time;
		  std::chrono::milliseconds ms(test);
		  t.start(ms);
	  };
	  s.pusherSystem.p3.timer.in.createTimer = [] (double time) {
		  TimerHelper t(GLOBAL_SYSTEM->pusherSystem.p1.timer.out.timeout);
		  int test = time;
		  std::chrono::milliseconds ms(test);
	      t.start(ms);
	  };
	  s.timer.port.in.createTimer = [] (double time){
		  TimerHelper t(GLOBAL_SYSTEM->pusherSystem.p1.timer.out.timeout);
		  int test = time;
		  std::chrono::milliseconds ms(test);
	      t.start(ms);
	  };

	  s.rebootTimer.port.in.createTimer = [] (double time){
		  TimerHelper t(GLOBAL_SYSTEM->pusherSystem.p1.timer.out.timeout);
		  int test = time;
		  std::chrono::milliseconds ms(test);
	      t.start(ms);
	  };


	//  s.belt.control.motor.in.turnClockwise


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


	  while(true){
	  }

	return 0;
}

