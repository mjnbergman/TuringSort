#ifndef _LDR_SENSOR;
#define _LDR_SENSOR;

class LDRSensor {
    public:
        void sensorSetup();
        void sensorLoop();
    private:
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