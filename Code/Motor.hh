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
    ~ Motor() {}
    void port_turnOn () {};
    void port_turnOff () {};
};




#endif /* CODE_MOTOR_HH_ */
