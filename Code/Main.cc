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

public:
    typedef std::chrono::milliseconds Interval;
    typedef std::function<void(void)> Timeout;

    void start(const Interval &interval,
               const Timeout &timeout)
    {
        running = true;

        th = thread([=]()
        {
            while (running == true) {
                this_thread::sleep_for(interval);
                timeout();
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



int main(){

	  dzn::locator locator;
	  dzn::runtime runtime;
	  dzn::illegal_handler illegal_handler;

//	  wiringPiSetup();



	  int dataPin = 5, latchPin = 6, clockPin = 7;
    byte motorBitsToSend = 0; //bits to send to the shift register for motor control


	  System s(locator.set(runtime).set(illegal_handler));

	  s.sensor.sensor.port_turnOn();


	  auto timerLambda = [] (System s, double ms) {
		  	  auto executionLamba = [] {

		  	  };
		//	  TimerHelper t(s.pusherSystem.p1.timer.out.timeout);
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

	  s.pusherSystem.p1.timer.in.createTimer = [] (double time) {
			//  TimerHelper t(s.pusherSystem.p1.timer.out.timeout);
	  };
	  s.pusherSystem.p2.timer.in.createTimer = [] (double time) {
			  //TimerHelper t(s.pusherSystem.p2.timer.out.timeout);
	  };
	  s.pusherSystem.p3.timer.in.createTimer = [] (double time) {
			  //TimerHelper t(s.pusherSystem.p3.timer.out.timeout);
	  };


	  s.pusherSystem.port.in.enqueueBox1 = [] (double ms){
		  //s.pusherSystem.p1.timer

	  };


	  while(true){
	  }

	return 0;
}

//writes the motorBitsToSend to the shift register for motor control
void registerWrite() {
  //turn off the output so the pins don't light up while the bits are being shifted
  digitalWrite(latchPin, LOW);

  //shifts the previous bits out and writes bitsToSend (most significant bit first)
  shiftOut(dataPin, clockPin, MSBFIRST, motorBitsToSend);

  //turn on the output again
  digitalWrite(latchPin, HIGH);
}

//turns a motor
//requires the motor number 0-3
//requires a boolean for turning direction turnLeft = false for clockwise
void turnMotor(int motor, bool turnLeft) {
  int bitToWrite = 0;
  bitToWrite = motor * 2;
  bitWrite(motorBitsToSend, bitToWrite, turnLeft);
  bitWrite(motorBitsToSend, bitToWrite + 1, !turnLeft);
  registerWrite();
}

//stops a motor
//requires the motor number 0-3
void stopMotor(int motor) {
  int bitToWrite = 0;
  bitToWrite = motor * 2;
  bitWrite(bitsToSend, bitToWrite, false);
  bitWrite(bitsToSend, bitToWrite + 1, false);
  registerWrite();
}
