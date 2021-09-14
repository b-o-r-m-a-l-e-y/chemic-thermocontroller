#include "device.h"
#include "TimerOne.h"
#include "interface.h"

Adafruit_MAX31855 thermocouple(THERMOCOUPLE_NCS_PIN);

void configureDevice(struct device_t* d)
{
    Serial.begin(9600);
    pinMode(HEATERS_PIN, OUTPUT);
    pinMode(MAGNET_PIN, OUTPUT);
    thermocouple.begin();
    configureDimmer(&(d->dimmer));
    loadSettingsFromFlash(&(d->settings), &(d->regulator));
    configureScheduler(d);
    configureRegulator(&(d->regulator), DEFAULT_T);
    d->settings.tempControlEnabled = 0;
    Timer1.initialize(1000);
    Timer1.attachInterrupt(timerCallback);
    Timer1.start();
    processMagnetPower(0);
}

void temperatureMeasurement(struct device_t* d)
{
    float externalTemp = (float) thermocouple.readCelsius();
    if (!isnan(externalTemp)) d->actualTemperature = externalTemp;
    float internalTemperature = (float) thermocouple.readInternal();
    if (!isnan(internalTemperature)) d->internalTemperature = internalTemperature;
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
            processLinearTemperature(d);
            if (d->settings.tempControlEnabled) {
                d->dimmer.requriedPowerValue = updateRegulator(&(d->regulator),
                                d->settings.requiredTemperature, d->actualTemperature);
            }
            d->pSheduler->measurementTask = 0;
        }
    }
}

void processMagnetPower(uint16_t powerValue)
{
    if (powerValue == 0) Timer1.disablePwm(MAGNET_PIN);
    else if (powerValue >= 1024) Timer1.pwm(MAGNET_PIN, 1024);
    else Timer1.pwm(MAGNET_PIN, powerValue);
}

void processLinearTemperature(struct device_t* d)
{
    if (d->settings.linearTemperatureControlFlag) {
        if (d->settings.linearTemperatureMsCounter <= d->settings.linearTemperatureTime) {
            float k = (d->settings.linearTemperature - d->settings.linearTemperature0) / d->settings.linearTemperatureTime;
            d->settings.requiredTemperature = k * d->settings.linearTemperatureMsCounter + d->settings.linearTemperature0;
            d->settings.linearTemperatureMsCounter += 200;
        }
        else d->settings.linearTemperatureControlFlag = 0;
    }
}