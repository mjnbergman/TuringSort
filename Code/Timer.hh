/*
 * Timer.hh
 *
 *  Created on: 22 Mar 2019
 *      Author: 20174570
 */

#include "TimerHelper.hh"

#ifndef TURINGSORT_CODE_TIMER_HH_
#define TURINGSORT_CODE_TIMER_HH_

struct Timer : skel::Timer{

private:
	TimerHelper* t;

public:
	Timer(const dzn::locator& dzn_locator) : skel::Timer(dzn_locator){};
	~Timer(){
		delete t;
	}
    void port_createTimer (double time){
      t = new TimerHelper(this->port.out.timeout);
	  int test = time;
	  std::chrono::milliseconds ms(test);
	  t->setDelay(test);
	  t->start();
    };
    void port_cancelTimer (){
    	t->stop();
    }
};



#endif /* TURINGSORT_CODE_TIMER_HH_ */
