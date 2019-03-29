/*
 * LightSensor.hh
 *
 *  Created on: 22 Mar 2019
 *      Author: 20174570
 */

#ifndef TURINGSORT_CODE_LIGHTSENSOR_HH_
#define TURINGSORT_CODE_LIGHTSENSOR_HH_


struct LightSensor : skel::LightSensor{

public:
	LightSensor(const dzn::locator& dzn_locator) : skel::LightSensor(dzn_locator){};
	void port_turnOn (){}
	void port_turnOff (){}
	void port_calibrate (){}
};



#endif /* TURINGSORT_CODE_LIGHTSENSOR_HH_ */
