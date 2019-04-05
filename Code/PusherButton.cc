/*
 * PusherButton.cc
 *
 *  Created on: 5 Apr 2019
 *      Author: Jari
 */

#include <PusherButton.hh>

PusherButton::PusherButton(int pin, Callback c)
: inputPin(pin), errorFunc(c)
{
	running = false;
	latestChangedStateTime = millis();
	stateIsUp = true;
}

void PusherButton::setExpectedState(bool up) {
	stateIsUp = up;
	latestChangedStateTime = millis();
}

void PusherButton::start() {
	running = true;

	th = thread([=]() {
		while (running) {
			long curMillis = millis();
			bool isUp = digitalRead(inputPin) == HIGH;
			if (latestChangedStateTime + GRACE_PERIOD < curMillis && stateIsUp != isUp) {
				errorFunc();
			}
			delay(POLLING_DELAY);
		}
	});
}

void PusherButton::stop() {
	running = false;
}

