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
      std::cout << "Someone fucked up a timer " << std::endl;
      t = new TimerHelper(this->port.out.timeout);
	 // int ms = time;
	 // std::chrono::duration<int, std::milli>;
	  int test = time;
	  std::chrono::milliseconds ms(test);
	  std::cout << "If it gets here Jari dies" << std::endl;
	  t->setDelay(test);
	  t->start();
	  std::cout << "Jari lives" << std::endl;
    };
    void port_cancelTimer (){
    	t->stop();
    }
};



#endif /* TURINGSORT_CODE_TIMER_HH_ */
