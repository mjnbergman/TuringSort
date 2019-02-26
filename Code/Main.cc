/*
 * Main.cc
 *
 *  Created on: 26 Feb 2019
 *      Author: 20174570
 */

#include <iostream>
#include "System.hh"
#include "wiringPi.h"

int main(){

	  dzn::locator locator;
	  dzn::runtime runtime;
	  dzn::illegal_handler illegal_handler;

//	  wiringPiSetup();

	  int motorPin = 5;

	  System s(locator.set(runtime).set(illegal_handler), motorPin);

	  s.sensor.sensor.port_turnOn();

	  while(true){
		//  std::cout << "Test Loop";
	  }

	return 0;
}


