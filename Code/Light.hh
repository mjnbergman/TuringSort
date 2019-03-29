/*
 * Light.hh
 *
 *  Created on: 22 Mar 2019
 *      Author: 20174570
 */


#ifndef TURINGSORT_CODE_LIGHT_HH_
#define TURINGSORT_CODE_LIGHT_HH_


struct Light : skel::Light{

public:
    Light(const dzn::locator& dzn_locator) : skel::Light(dzn_locator){};
    void port_turnOn (){}
    void port_turnOff (){}
};



#endif /* TURINGSORT_CODE_LIGHT_HH_ */
