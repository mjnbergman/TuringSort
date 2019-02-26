/*
 * LightSensor.hh
 *
 *  Created on: 22 Feb 2019
 *      Author: 20174570
 */


#ifndef CODE_LIGHTSENSOR_HH_
#define CODE_LIGHTSENSOR_HH_

struct LightSensor : public skel::LightSensor{
    ~ LightSensor() {}
    LightSensor(const dzn::locator& dzn_locator) : skel::LightSensor(dzn_locator){};
    void port_turnOn () {std::cout << "Test Turn On";};
    void port_turnOff () {};
    void port_calibrate () {};
};




#endif /* CODE_LIGHTSENSOR_HH_ */
