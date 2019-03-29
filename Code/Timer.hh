/*
 * Timer.hh
 *
 *  Created on: 22 Mar 2019
 *      Author: 20174570
 */

#ifndef TURINGSORT_CODE_TIMER_HH_
#define TURINGSORT_CODE_TIMER_HH_

struct Timer : skel::Timer{

public:
	Timer(const dzn::locator& dzn_locator) : skel::Timer(dzn_locator){};
    void port_createTimer (double time){}
    void port_cancelTimer (){}
};



#endif /* TURINGSORT_CODE_TIMER_HH_ */
