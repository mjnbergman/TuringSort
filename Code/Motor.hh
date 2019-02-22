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
    std::ostream& stream_members(std::ostream& os) const { return os; } // @suppress("Type cannot be resolved")
    void port_turnOn () = 0;
    void port_turnOff () = 0;
};




#endif /* CODE_MOTOR_HH_ */
