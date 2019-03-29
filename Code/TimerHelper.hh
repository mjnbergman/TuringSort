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

public:
    typedef std::chrono::milliseconds Interval;
    typedef std::function<void(void)> Timeout;

    TimerHelper(Timeout timeoutFunc) : timeoutFunc(timeoutFunc){};
    TimerHelper(){};
    void start(const Interval &interval)
    {
        running = true;

        th = thread([=]()
        {
            while (running == true) {
                this_thread::sleep_for(interval);
                this->timeoutFunc();
            }
        });

// [*]
        th.join();
    }

    void stop()
    {
        running = false;
    }
};



#endif /* TURINGSORT_CODE_TIMERHELPER_HH_ */
