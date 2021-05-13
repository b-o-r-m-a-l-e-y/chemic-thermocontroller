#include "device.h"
#include "TimerOne.h"

Adafruit_MAX31855 thermocouple(THERMOCOUPLE_NCS_PIN);

void configureDevice(struct device_t* d)
{
    Serial.begin(9600);
    thermocouple.begin();
    configureDimmer(&(d->dimmer));
    // Load settings
    loadDefaultSettings(&(d->settings));
    configureScheduler(&(d->settings), d->pSheduler);
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