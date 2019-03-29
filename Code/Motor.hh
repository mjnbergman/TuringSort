/*
 * Motor.hh
 *
 *  Created on: 22 Mar 2019
 *      Author: 20174570
 */

#ifndef TURINGSORT_CODE_MOTOR_HH_
#define TURINGSORT_CODE_MOTOR_HH_

#include <wiringPi.h>
#include <wiringShift.h>

typedef uint8_t byte;


struct Motor : skel::Motor{
private:

  int motorPin;

  int dataPin;
  int latchPin;
  int clockPin;

public:

    static byte motorBitsToSend; //bits to send to the shift register for motor control

    Motor(const dzn::locator& dzn_locator) : skel::Motor(dzn_locator){
    };
    void port_turnClockwise (){
    	turnMotor(false);
    }
    void port_turnOff (){
    	stopMotor();
    }
    void port_turnCounterClockwise (){
    	turnMotor(true);
    }

    //writes the motorBitsToSend to the shift register for motor control
    void registerWrite() {
      //turn off the output so the pins don't light up while the bits are being shifted
      digitalWrite(latchPin, LOW);

      //shifts the previous bits out and writes bitsToSend (most significant bit first)
      shiftOut(dataPin, clockPin, MSBFIRST, Motor::motorBitsToSend);

      //turn on the output again
      digitalWrite(latchPin, HIGH);
    }

    //turns a motor
    //requires the motor number 0-3
    //requires a boolean for turning direction turnLeft = false for clockwise
    void turnMotor(bool turnLeft) {
      int bitToWrite = 0;
      bitToWrite = this->motorPin * 2;
  //    bitWrite(motorBitsToSend, bitToWrite, turnLeft);

      Motor::motorBitsToSend |= (1 << bitToWrite);

 //     bitWrite(motorBitsToSend, bitToWrite + 1, !turnLeft);

      Motor::motorBitsToSend &= ~(1 << (bitToWrite + 1));

      registerWrite();
    }

    //stops a motor
    //requires the motor number 0-3
    void stopMotor() {
      int bitToWrite = 0;
      bitToWrite = this->motorPin * 2;
  //    bitWrite(bitsToSend, bitToWrite, false);

      Motor::motorBitsToSend &= ~(1 << bitToWrite);

  //    bitWrite(bitsToSend, bitToWrite + 1, false);

      Motor::motorBitsToSend &= ~(1 << (bitToWrite + 1));
      registerWrite();
    }

    void setMotorNumber(int pin){
    	this->motorPin = pin;
    }
    void setPins(int dataPin, int latchPin, int clockPin){
    	this->dataPin = dataPin;
    	this->latchPin = latchPin;
    	this->clockPin = clockPin;
    }
};



#endif /* TURINGSORT_CODE_MOTOR_HH_ */
