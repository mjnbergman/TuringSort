/*
 * SensorHelper.hh
 *
 *  Created on: 1 Apr 2019
 *      Author: Jari Martens
 */

#include <iostream>
#include <thread>

#ifndef TURINGSORT_CODE_SENSORHELPER_HH_
#define TURINGSORT_CODE_SENSORHELPER_HH_

using namespace std;

class SensorHelper
{
    thread th;
    bool running = false;
    std::function<void(void)> loopFunc;
public:
    typedef std::function<void(void)> Loop;

    SensorHelper(Loop loopFunc) : loopFunc(loopFunc){};
    void start()
    {
        running = true;

        th = thread([=]()
        {
            while (running == true) {
                this->loopFunc();
            }
        });
        th.detach();
    }

    void stop()
    {
        running = false;
    }
};



#endif /* TURINGSORT_CODE_TIMERHELPER_HH_ */
