/*
 * LightSensor.hh
 *
 *  Created on: 22 Feb 2019
 *      Author: 20174570
 */

#include "System.hh"

#include <iostream>

#ifndef CODE_LIGHTSENSOR_HH_
#define CODE_LIGHTSENSOR_HH_

struct LightSensor : public skel::LightSensor{
    ~ LightSensor() {}
    std::ostream& stream_members(std::ostream& os) const { return os; } // @suppress("Type cannot be resolved")
    private:
    void port_turnOn () = 0;
    void port_turnOff () = 0;
    void port_calibrate () = 0;
};




#endif /* CODE_LIGHTSENSOR_HH_ */
