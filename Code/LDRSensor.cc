#include "LDRSensor.hh"


LDRSensor::LDRSensor(LDRSensor::Callback error, LDRSensor::Callback white, LDRSensor::Callback black)
: callbackError(error), callbackWhite(white), callbackBlack(black)
{
}

/// SETUP FUNCTIONS ///
void LDRSensor::sensorSetup(){
  //create null hypothesis

  //setup charging stuff initially
  pinMode(measureWhitePin, INPUT);
  pinMode(measureBlackPin, INPUT);
//  digitalWrite(chargePin, LOW);
  std::cout << "Reached the end of setup...";

  //Serial.begin(9600); // Necessary to print data to serial monitor over USB
}

void LDRSensor::calibrate(){
//	sensorSetup();
/*	std::cout << "Before calibration" << std::endl;
  nullHypothesis = 0;
  //sampleSize = 11;
  unsigned long measurements[11];
  for(int i = 0; i < sampleSize; i++){
    doMeasurement(true); //10 iterations of loop
    measurements[i] = nullHypothesis;
    std::cout << "After measuring loop: " << i << std::endl;
  }
  
  //time passed to do sampleSize measurements
  sort(measurements, 11);
  nullHypothesis = measurements[5];
  //takes the mean of the measurements

  std::cout << "ready to start measuring with" << std::endl;
  std::cout << "null:" + nullHypothesis << std::endl;
*/
 // delay(2000);
}

/// MAIN LOOP FUNCTIONS ///
void LDRSensor::sensorLoop(){
   this->generateColorEvent(this->doMeasurement());
}


LDRSensor::Detected LDRSensor::doMeasurement(){
/*  digitalWrite(chargePin, HIGH); // Begins charging the capacitor

void LDRSensor::doMeasurement(bool isSetup){
  digitalWrite(CHARGE_PIN, HIGH); // Begins charging the capacitor

  startTime = micros();

  bool chargeError = chargeCapacitor();
  if (chargeError) return;

  elapsedTime = micros() - startTime; // Determines how much time it took to charge capacitor
  if (isSetup) nullHypothesis = elapsedTime;
  
  stopChargingCapacitor();
  
  printDiagnostics();

  Detected d = determineColor();
  if (d == EXIT) return; //exit loop
  
  if (!isSetup){ //generate event (color or error) based on measurement, iff is not setup
    checkResult(d);
  }

  stopDischargingCapacitor(); */
	/*pinMode(measurePin, OUTPUT);
	digitalWrite(measurePin, LOW);
	delay(1);
	pinMode(measurePin, INPUT);

	int count = 0;

	while(digitalRead(measurePin) == LOW){
		count += 1;
	}

	nullHypothesis = count;
*/


	if(digitalRead(measureBlackPin) == HIGH && digitalRead(measureWhitePin) == LOW){
		return LDRSensor::Detected::BLACK;
	}else if(digitalRead(measureWhitePin) == HIGH && digitalRead(measureBlackPin) == LOW){
		return LDRSensor::Detected::WHITE;
	}else if(digitalRead(measureWhitePin) == HIGH && digitalRead(measureBlackPin) == HIGH){
		return LDRSensor::Detected::ERROR;
	}else{
		return LDRSensor::Detected::NOTHING;
	}
}
/*
LDRSensor::Detected LDRSensor::determineColor(){
  if(elapsedTime < 100){
    //happens when capacitor was not charged but still got here in execution. Shouldn't really happen, but in case it does...
    return NOTHING;
  } else if (elapsedTime < (0.8 * (float) nullHypothesis)) {

    if (!firstWhite && secondWhite){
      secondWhite = false;
      whiteish = elapsedTime;
    } 
    
    if (firstWhite){ //return to do another measure quickly
      firstWhite = false;
      redoIn(DELAY_BETWEEN_DISKS);
      return EXIT; //exit loop
    }

    return WHITE;
  } else if (elapsedTime > (1.2 * (float) nullHypothesis)){

    if (!firstBlack && secondBlack){
      secondBlack = false;
      blackish = elapsedTime;
    } 
    
    if (firstBlack){
      firstBlack = false;
      redoIn(DELAY_BETWEEN_DISKS);
      return EXIT; //exit loop  
    }
    
    return BLACK;
  } else {
    return NOTHING;
  }
}

void LDRSensor::checkResult(Detected d){
  bool susValue = checkLEDs(elapsedTime, d);
  if (susValue) {
    errorCount++; //this color was not expected
    std::cout << "WARNING: LED(s) might be off." << std::endl;
  } else {
    errorCount = 0; //this color was expected
  }

  if (errorCount > TOLERANCE) {
    genErrorEvent(LED);
  } else {
    generateColorEvent(d);
  }  
}
*/

/**
 * Prepares for doing another measurement after (ms). 
 * Cannot use delay because capacitor circuit must be prepared

void LDRSensor::redoIn(unsigned long ms) {
  long time_1 = millis();
  while (digitalRead(MEASURE_PIN) == HIGH){
    bool error = LDRErrorGuard(time_1);
      if (error) {

        genErrorEvent(LDR);
        break;
      } //discharge
  }
  while (millis() - time_1 < ms); //delay ms while taking the other while in account
  pinMode(DISCHARGE_PIN, INPUT); // Prevents capacitor from discharging
}

/// CAPACITOR CONTROL FUNCTIONS ///
bool LDRSensor::chargeCapacitor(){ //returns wether or not an error occured
  while (digitalRead(MEASURE_PIN) == LOW) {
    //wait for the capacitor to charge the pin to HIGH
    bool error = LDRErrorGuard(startTime);
    std::cout << "Charging since..." << startTime << " for " << (micros() - startTime) << " micros!" << std::endl;
    if (error) {
    	 // TODO INSERT DEBUGGING COUT HERE
      genErrorEvent(LDR);
      stopChargingCapacitor();
      stopDischargingCapacitor();
      return true; //exit loop
    }
  }
  return false;
}
*/
/*
void LDRSensor::stopChargingCapacitor(){
  digitalWrite(CHARGE_PIN, LOW); // Stops charging capacitor
  pinMode(DISCHARGE_PIN, OUTPUT);
  digitalWrite(DISCHARGE_PIN, LOW); // Allows capacitor to discharge
}

void LDRSensor::stopDischargingCapacitor(){
  unsigned long time_1 = micros();
  while (digitalRead(MEASURE_PIN) == HIGH){
    //let the pin fully discharge, if not done already
    bool error = LDRErrorGuard(time_1);
    if (error){
      //an error was detected. Generate the error event, but also continue this method to properly reset the capacitor. Make sure no color event is generated by setting 'setup' to true
      genErrorEvent(LDR);
      break;
    }
  }
  pinMode(DISCHARGE_PIN, INPUT); // Prevents capacitor from discharging
}
*/
/// DEZYNE EVENT GENERATORS ///
void LDRSensor::generateColorEvent(Detected d){
  switch(d){
      case WHITE:
        genWhiteEvent(); delay(DELAY_BETWEEN_MEASUREMENTS); break;
      case BLACK:
        genBlackEvent(); delay(DELAY_BETWEEN_MEASUREMENTS); break;
      case NOTHING: 
        genNothingEvent(); break;
      case ERROR:
    	genErrorEvent(LDRSensor::Error::LDR); break;
    }  
}

/**
 * DEZYNE EVENT GENERATOR
 */
void LDRSensor::genWhiteEvent(){
  unsigned long curMillis = millis();
  if (previousDetected == LDRSensor::Detected::WHITE && curMillis - previousEncounter >= SUBSEQUENCE_DELAY){ //saw a disk the very previous measure
      genErrorEvent(DDISK);
      return;
  }else if(previousDetected == LDRSensor::Detected::WHITE && curMillis - previousEncounter < SUBSEQUENCE_DELAY){
	  return;
  }
  previousEncounter = curMillis;
  previousDetected = LDRSensor::Detected::WHITE;
  callbackWhite();
  std::cout << "WHITE" << std::endl;
}

/**
 * DEZYNE EVENT GENERATOR
 */
void LDRSensor::genBlackEvent(){
  unsigned long curMillis = millis();
  if (previousDetected == LDRSensor::Detected::BLACK && curMillis - previousEncounter >= SUBSEQUENCE_DELAY){//saw a disk the very previous measure
    previousEncounter = curMillis;
	genErrorEvent(DDISK);
    return;
  }else if(previousDetected == LDRSensor::Detected::BLACK && curMillis - previousEncounter < SUBSEQUENCE_DELAY){
	 return;
  }
  previousEncounter = curMillis;
  previousDetected = LDRSensor::Detected::BLACK;
  callbackBlack();
  std::cout << "BLACK" << std::endl;
}

/**
 * DEZYNE EVENT GENERATOR
 */
void LDRSensor::genNothingEvent(){
  previousDetected = LDRSensor::Detected::NOTHING;
 // std::cout << "NOTHING" << std::endl;
  //do not need to generate an event for dezyne at the time
}

/**
 * DEZYNE EVENT GENERATOR
 */
void LDRSensor::genErrorEvent(Error e){
  std::cout << "ERROR: ";
  switch(e){
    case LDR: std::cout << "LDR cannot make measurements at this time" << std::endl;  break;
    case LED: std::cout << "Light level has been changed after calibration." << std::endl; break;
    case DDISK: std::cout << "Concurrent disk detection is not allowed!" << std::endl; break;
  }  
  this->callbackError();
}

/// ERROR CHECKERS ///
/**
 * Compare started time with current time (micros) 

bool LDRSensor::LDRErrorGuard(unsigned long started){
  return (micros() - started) > 10000000L; //true iff has been 1 second since started. LDR hasn't measured a thing. error!
}
*/
/**
 * Returns wether or not a led mightve turned off

bool LDRSensor::checkLEDs(unsigned long colorValue, Detected d){
  switch(d){
    case WHITE: return (colorValue > (1+MEASUREMENT_RANGE) * whiteish || colorValue < (1-MEASUREMENT_RANGE) * whiteish); //color is more than 20% darker than before.
    case BLACK: return (colorValue > (1+MEASUREMENT_RANGE) * blackish || colorValue < (1-MEASUREMENT_RANGE) * blackish); //color is more than 20% darker than before.
    case NOTHING: return false; //fine no matter what
  }
}
*/

/// MISC FUNCTIONS ///
void LDRSensor::sort(unsigned long arr[], int n){
  //all these arrs are size 11, fortunately.
  int i, j;
  unsigned long key;
    for (i = 1; i < n; i++) { 
        key = arr[i]; 
        j = i - 1; 
        /* Move elements of arr[0..i-1], that are 
          greater than key, to one position ahead 
          of their current position */
        while (j >= 0 && arr[j] > key) { 
            arr[j + 1] = arr[j]; 
            j = j - 1; 
        } 
        arr[j + 1] = key; 
    }
  //  return arr;
}

void LDRSensor::printDiagnostics(){
  std::cout << (((float) elapsedTime / (float) nullHypothesis) * 100); std::cout << "%";
  std::cout << std::endl;
  std::cout << ("____") << std::endl;
  std::cout << ("blackish: "); std::cout << (((float) blackish / (float) nullHypothesis) * 100); std::cout << ("%") << std::endl;
  std::cout << ("whiteish: "); std::cout << (((float) whiteish / (float) nullHypothesis) * 100); std::cout << ("%") << std::endl;
  std::cout <<("____") << std::endl;
}
