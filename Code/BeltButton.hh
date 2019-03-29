/*
 * TimerHelper.hh
 *
 *  Created on: 29 Mar 2019
 *      Author: 20174570
 */

#include <iostream>
#include <thread>
#include "System.hh"
#include "wiringPi.h"

#ifndef TURINGSORT_CODE_TIMERHELPER_HH_
#define TURINGSORT_CODE_TIMERHELPER_HH_

using namespace std;

class BeltButton
{
    thread th;
    bool running = false;
    int inputPin; //set this equal to the correct pin
    const int maxDelay = 750;
    long currentMillis = 0;
    long oldMilis = 0;
    std::function<void(void)> errorFunc;

public:
    BeltButton(int inputPin, std::function<void(void)> errorFunction) : inputPin(inputPin), errorFunc(errorFunction){};
    void start()
    {
        running = true;
        pinMode(inputPin, INPUT);

        th = thread([=]()
        {
            while (running == true) {
              currentMillis = millis();
              if ((currentMillis - oldMillis) >= maxDelay) {
                errorFunc();
              }
              if (digitalRead(inputPin) == HIGH) {
                oldMillis = currentMillis;
                while(digitalRead(inputPin) == HIGH) {
                  currentMillis = millis();
                  if ((currentMillis - oldMillis) >= maxDelay) {
                    errorFunc();
                  }
                }
                oldMillis = currentMillis;
              }
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
