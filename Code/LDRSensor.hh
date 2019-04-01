#ifndef _LDR_SENSOR;
#define _LDR_SENSOR;

#include <wiringPi.h>
#include <iostream>

class LDRSensor {
    public:
        void sensorSetup();
        void sensorLoop();
    private:


        /// PINS ///
        int chargePin = 13;
        int dischargePin = 11; //speeds up discharging process, not necessary though
        int measurePin = 2;

        /// TIMER ///
        unsigned long startTime;
        unsigned long elapsedTime;

        /// CALIBRATION VARS ///
        const int sampleSize = 11;
        unsigned long nullHypothesis;

        /// COLOR VERIFICATION VARS ///
        unsigned long blackish;
        unsigned long whiteish;
        bool firstWhite = true;
        bool firstBlack = true;
        bool secondWhite = true;
        bool secondBlack = true;

        bool detected = false;

        /// ERROR VARS ///
        int errorCount = 0; //counts measurements that aren't nothing nor whiteish nor blackish
        const int TOLERANCE = 3;

        /// ENUMS ///
        enum Detected {BLACK, WHITE, NOTHING, EXIT};
        enum Error {LED, LDR, DDISK};

        void calibrate();
        void doMeasurement(bool isSetup);
        Detected determineColor();
        void checkResult(Detected d);
        void redoIn(unsigned long ms);
        bool chargeCapacitor();
        void stopChargingCapacitor();
        void stopDischargingCapacitor();
        void generateColorEvent(Detected d);
        void genWhiteEvent();
        void genBlackEvent();
        void genNothingEvent();
        void genErrorEvent(Error e);
        bool LDRErrorGuard(unsigned long started);
        bool checkLEDs(unsigned long colorValue, Detected d);
        void sort(unsigned long arr[], int n);
        void printDiagnostics();

};

#endif
