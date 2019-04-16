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

/**
 * The TimerHelper class functions like a wrapper class for the creation and execution of seperate threads.
 * It allows you to pass in a lambda function and a delay (which is internally passed to a std::chrono:milliseconds value).
 * After you call the start() function of a TimerHelper object, it will create a seperate thread, sleep this thread
 * for the delay you specified, and then execute your lambda function.
 */
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
        //	std::cout << "In de thread!!!" << std::endl;
            if (running == true) {
            //	std::cout << "Running is true, de thread runt!!!" << " met delay: " << this->delayTime.count() << std::endl;
                this_thread::sleep_for(this->delayTime);
             //   std::cout << "Klaar met slapie!!! Execute nu de functie..." << " met delay: " << this->delayTime.count() << std::endl;
                this->timeoutFunc();
             //   std::cout << "Klaar met het uitvoeren van de callback functie!!!" << std::endl;
            }
        });

// [*]
        th.detach();
    }

    void stop()
    {
        running = false;
    }
    void setDelay(int i){
    	  std::cout << "De input is: " << i << std::endl;
		  std::chrono::milliseconds ms1(i);
		  this->delayTime = ms1;
		  std::cout << "De output is: " << this->delayTime.count() << std::endl;
    }
    std::chrono::milliseconds getDelay(){
    	return this->delayTime;
    }
};



#endif /* TURINGSORT_CODE_TIMERHELPER_HH_ */
