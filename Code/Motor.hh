/*
 * Motor.hh
 *
 *  Created on: 22 Mar 2019
 *      Author: 20174570
 */

#ifndef TURINGSORT_CODE_MOTOR_HH_
#define TURINGSORT_CODE_MOTOR_HH_

#include "wiringPi.h"

struct Motor : skel::Motor{
private:
  static byte motorBitsToSend = 0; //bits to send to the shift register for motor control

public:
    Motor(const dzn::locator& dzn_locator) : skel::Motor(dzn_locator){};
    void port_turnClockwise (){}
    void port_turnOff (){}
    void port_turnCounterClockwise (){}

    //writes the motorBitsToSend to the shift register for motor control
    void registerWrite() {
      //turn off the output so the pins don't light up while the bits are being shifted
      digitalWrite(latchPin, LOW);

      //shifts the previous bits out and writes bitsToSend (most significant bit first)
      shiftOut(dataPin, clockPin, MSBFIRST, motorBitsToSend);

      //turn on the output again
      digitalWrite(latchPin, HIGH);
    }

    //turns a motor
    //requires the motor number 0-3
    //requires a boolean for turning direction turnLeft = false for clockwise
    void turnMotor(int motor, bool turnLeft) {
      int bitToWrite = 0;
      bitToWrite = motor * 2;
      bitWrite(motorBitsToSend, bitToWrite, turnLeft);
      bitWrite(motorBitsToSend, bitToWrite + 1, !turnLeft);
      registerWrite();
    }

    //stops a motor
    //requires the motor number 0-3
    void stopMotor(int motor) {
      int bitToWrite = 0;
      bitToWrite = motor * 2;
      bitWrite(bitsToSend, bitToWrite, false);
      bitWrite(bitsToSend, bitToWrite + 1, false);
      registerWrite();
    }
};



#endif /* TURINGSORT_CODE_MOTOR_HH_ */
