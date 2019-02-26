/*
 * Light.hh
 *
 *  Created on: 22 Feb 2019
 *      Author: 20174570
 */

#ifndef CODE_LIGHT_HH_
#define CODE_LIGHT_HH_

struct Light: public skel::Light{
	Light(const dzn::locator& loc) : skel::Light(loc){};
    void port_turnOn () {};
    void port_turnOff () {};
};




#endif /* CODE_LIGHT_HH_ */
