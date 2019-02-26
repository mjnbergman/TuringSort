/*
 * Motor.hh
 *
 *  Created on: 22 Feb 2019
 *      Author: 20174570
 */

#include "System.hh"

#ifndef CODE_MOTOR_HH_
#define CODE_MOTOR_HH_

struct Motor : public skel::Motor{

public:

	Motor(const dzn::locator& dzn_locator, int pin) : skel::Motor(dzn_locator), motorPin(pin){
		//pinMode(motorPin, OUTPUT);
		std::cout << "motorPin initialized as output at pin 5!" << std::endl;
	};
    ~ Motor() {}
    void port_turnOn () {
    	std::cout << "Motor turned on!";
    	//DigitalWrite(motorPin, HIGH);
    };
    void port_turnOff () {
    	std::cout << "Motor turned off!";
    	//DigitalWrite(motorPin, LOW);
    };

private:
	int motorPin;
};




#endif /* CODE_MOTOR_HH_ */
