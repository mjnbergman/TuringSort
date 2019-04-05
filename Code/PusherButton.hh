/*
 * PusherButton.hh
 *
 *  Created on: 5 Apr 2019
 *      Author: Jari
 */

#include <iostream>
#include <thread>
#include "System.hh"
#include "wiringPi.h"

#ifndef CODE_PUSHERBUTTON_HH_
#define CODE_PUSHERBUTTON_HH_

using namespace std;

class PusherButton {
private:
	const int GRACE_PERIOD = 500;
	const int POLLING_DELAY = 100;
	std::function<void(void)> errorFunc;
	int inputPin;
	long latestChangedStateTime;
	bool stateIsUp;


	thread th;
	bool running;

public:
	typedef std::function<void(void)> Callback;

	PusherButton(int pin, Callback c);

	void setExpectedState(bool up);
	void start();
	void stop();
};

#endif /* CODE_PUSHERBUTTON_HH_ */
