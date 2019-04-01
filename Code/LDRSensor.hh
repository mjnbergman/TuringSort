#ifndef _LDR_SENSOR;
#define _LDR_SENSOR;

#include <wiringPi.h>
#include <iostream>
#include <thread>

class LDRSensor {
    public:
		typedef std::function<void(void)> Callback;
		LDRSensor(Callback error, Callback white, Callback black);
        void sensorSetup();
        void calibrate();
        void sensorLoop();
    private:
        std::function<void(void)> callbackError;
        std::function<void(void)> callbackWhite;
        std::function<void(void)> callbackBlack;


        /// PINS ///
        const int CHARGE_PIN = 3;
        const int DISCHARGE_PIN = 0; //speeds up discharging process, not necessary though
        const int MEASURE_PIN = 2;

        // PREVIOUSLY MAGIC NUMBERS
        const int DELAY_BETWEEN_MEASUREMENTS = 750;
        const int DELAY_BETWEEN_DISKS = 100;
        const double MEASUREMENT_RANGE = 0.2;

        /// TIMER ///
        unsigned long startTime = 0;
        unsigned long elapsedTime = 0;

        /// CALIBRATION VARS ///
        const int SAMPLE_SIZE = 11;
        unsigned long nullHypothesis = 0;

        /// COLOR VERIFICATION VARS ///
        unsigned long blackish = 0;
        unsigned long whiteish = 0;
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
