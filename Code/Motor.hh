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
      std::cout << "Inside registerWrite()" << std::endl;
      //turn off the output so the pins don't light up while the bits are being shifted
      digitalWrite(latchPin, LOW);
      std::cout << "Past the latchPin toggle! op " << this->latchPin << std::endl;
      //delay(50);
      //shifts the previous bits out and writes bitsToSend (most significant bit first)
      shiftOut(dataPin, clockPin, MSBFIRST, Motor::motorBitsToSend);
      std::cout << "Past the shiftOut statement! Data en clock: " << this->dataPin << ", " << this->clockPin << std::endl;
      //delay(50);
      //turn on the output again
      digitalWrite(latchPin, HIGH);
      std::cout << "Past the second latchPin toggle! motorPin: " << this->motorPin << std::endl;
    }

    //turns a motor
    //requires the motor number 0-3
    //requires a boolean for turning direction turnLeft = false for clockwise
    void turnMotor(bool turnLeft) {
      int bitToWrite = 0;
      bitToWrite = this->motorPin * 2;
  //    bitWrite(motorBitsToSend, bitToWrite, turnLeft);
      std::cout << "Uberhaubt in de functie?" << std::endl;
      if(turnLeft){
    	  Motor::motorBitsToSend |= (1 << bitToWrite);
    	  Motor::motorBitsToSend &= ~(1 << (bitToWrite + 1));
    	  std::cout << "De bits to send zijn: " << std::to_string(Motor::motorBitsToSend) << std::endl;
    	  if(Motor::motorBitsToSend == 0){
    		  std::cout << "Zero!" << std::endl;
    	  }
      }else{
    	  Motor::motorBitsToSend &= ~(1 << bitToWrite);
    	  Motor::motorBitsToSend |= (1 << (bitToWrite + 1));
    	  std::cout << "Toch false wtf?" << std::endl;
      }


 //     bitWrite(motorBitsToSend, bitToWrite + 1, !turnLeft);

     // Motor::motorBitsToSend &= ~(1 << (bitToWrite + 1));

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

		pinMode(dataPin, OUTPUT);
		pinMode(latchPin, OUTPUT);
		pinMode(clockPin, OUTPUT);
    }
};



#endif /* TURINGSORT_CODE_MOTOR_HH_ */
