/*
 * TimerHelper.hh
 *
 *  Created on: 29 Mar 2019
 *      Author: 20174570
 */

#include <iostream>
#include <thread>

#ifndef TURINGSORT_CODE_TIMERHELPER_HH_
#define TURINGSORT_CODE_TIMERHELPER_HH_

using namespace std;

class TimerHelper
{
    thread th;
    bool running = false;
    std::function<void(void)> timeoutFunc;
    std::chrono::milliseconds delayTime;
public:
    typedef std::chrono::milliseconds Interval;
    typedef std::function<void(void)> Timeout;

    TimerHelper(Timeout timeoutFunc) : timeoutFunc(timeoutFunc){};
    void start()
    {
        running = true;

        th = thread([=]()
        {
        	std::cout << "In de thread!!!" << std::endl;
            if (running == true) {
            	std::cout << "Running is true, de thread runt!!!" << std::endl;
                this_thread::sleep_for(this->delayTime);
                std::cout << "Klaar met slapie!!! Execute nu de functie..." << std::endl;
                this->timeoutFunc();
                std::cout << "Klaar met het uitvoeren van de callback functie!!!" << std::endl;
            }
        });

// [*]
        th.join();
    }

    void stop()
    {
        running = false;
    }
    void setDelay(int i){
		  std::chrono::milliseconds ms1(i);
		  this->delayTime = ms1;
    }
};



#endif /* TURINGSORT_CODE_TIMERHELPER_HH_ */
