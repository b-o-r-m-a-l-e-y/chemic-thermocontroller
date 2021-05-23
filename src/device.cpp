#include "device.h"
#include "TimerOne.h"
#include "interface.h"

Adafruit_MAX31855 thermocouple(THERMOCOUPLE_NCS_PIN);

void configureDevice(struct device_t* d)
{
    Serial.begin(9600);
    thermocouple.begin();
    configureDimmer(&(d->dimmer));
    // Load settings
    loadDefaultSettings(&(d->settings));
    configureScheduler(&(d->settings), d->pSheduler);
    configureRegulator(&(d->regulator), DEFAULT_KP, DEFAULT_KI, DEFAULT_T);
    // Just for first tests
    d->dimmer.requriedPowerValue = 32;
    Timer1.initialize(1000);
    Timer1.attachInterrupt(timerCallback);
    Timer1.start();
}

void temperatureMeasurement(struct device_t* d)
{
    d->actualTemperature = (float) thermocouple.readCelsius();
    d->internalTemperature = (float) thermocouple.readInternal();
    d->flagsThermocouple = thermocouple.readError();
}

void mainLoop(struct device_t* d)
{
    while(1)
    {
        processSerial(d);
        if (d->pSheduler->telemetryTask) {
            sendTelemetry(d);
            d->pSheduler->telemetryTask = 0;
        }
        if (d->pSheduler->regulatorTask) {
            processDimmerMeasurements(&(d->dimmer));
            d->pSheduler->regulatorTask = 0;
        }
        if (d->pSheduler->measurementTask) {
            temperatureMeasurement(d);
            //updateRegulator(&(device.regulator), device.settings.requiredTemperature, device.actualTemperature);
            d->pSheduler->measurementTask = 0;
        }
    }
}