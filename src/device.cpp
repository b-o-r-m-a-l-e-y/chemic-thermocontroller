#include "device.h"

Adafruit_MAX31855 thermocouple(THERMOCOUPLE_NCS_PIN);

void configureDevice(struct device_t* d)
{
    Serial.begin(9600);
    thermocouple.begin();
    // Load settings
    loadDefaultSettings(&(d->settings));
}

void temperatureMeasurement(struct device_t* d)
{
    d->actualTemperature = (float) thermocouple.readCelsius();
    d->internalTemperature = (float) thermocouple.readInternal();
    d->flagsThermocouple = thermocouple.readError();
}