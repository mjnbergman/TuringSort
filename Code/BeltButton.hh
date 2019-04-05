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

#ifndef TURINGSORT_BELTBUTTON_HH__
#define TURINGSORT_BELTBUTTON_HH__

using namespace std;

class BeltButton
{
    thread th;
    bool running = false;
    int inputPin; //set this equal to the correct pin
    const int MAX_DELAY = 750;
    long currentMillis = 0;
    long oldMillis = 0;
    std::function<void(void)> errorFunc;

public:
    BeltButton(int inputPin, std::function<void(void)> errorFunction) : inputPin(inputPin), errorFunc(errorFunction) {
        pinMode(inputPin, INPUT);
    };
    void start()
    {
        running = true;

        th = thread([=]()
        {
            while (running == true) {
              currentMillis = millis();
              if ((currentMillis - oldMillis) >= MAX_DELAY) {
                errorFunc();
                running = false;
              }
              if (digitalRead(inputPin) == HIGH) {
                oldMillis = currentMillis;
                while(digitalRead(inputPin) == HIGH) {
                  currentMillis = millis();
                  if ((currentMillis - oldMillis) >= MAX_DELAY) {
                    errorFunc();
                    running = false;
                  }
                }
                oldMillis = currentMillis;
              }
            }
        });
        th.join();
    }

    void stop()
    {
        running = false;
    }
};



#endif /* TURINGSORT_BELTBUTTON_HH_ */
