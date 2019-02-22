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
    private:
    void port_turnOn () {};
    void port_turnOff () {};
    void port_calibrate () {};
};




#endif /* CODE_LIGHTSENSOR_HH_ */
