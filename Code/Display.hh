/*
 * Display.hh
 *
 *  Created on: 22 Feb 2019
 *      Author: 20174570
 */

#include "System.hh"

#ifndef CODE_DISPLAY_HH_
#define CODE_DISPLAY_HH_

struct Display : public skel::Display{
    ~ Display() {}
    void port_turnOn () {};
    void port_turnOff () {};
    void port_output (std::string output) {};
};

#endif /* CODE_DISPLAY_HH_ */
