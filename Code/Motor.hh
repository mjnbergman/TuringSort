/*
 * Motor.hh
 *
 *  Created on: 22 Mar 2019
 *      Author: 20174570
 */

#ifndef TURINGSORT_CODE_MOTOR_HH_
#define TURINGSORT_CODE_MOTOR_HH_


struct Motor : skel::Motor{

public:
    Motor(const dzn::locator& dzn_locator) : skel::Motor(dzn_locator){};
    void port_turnClockwise (){}
    void port_turnOff (){}
    void port_turnCounterClockwise (){}
};



#endif /* TURINGSORT_CODE_MOTOR_HH_ */
