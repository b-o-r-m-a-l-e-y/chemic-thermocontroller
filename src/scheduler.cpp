#include "scheduler.h"
#include "Arduino.h"

// Sorry for this, but in current realization
// I couldn`t pass a parameter to timerCallback.
// Really need to reimplement this
struct scheduler_t scheduler;

void configureScheduler(struct device_t* d)
{
    scheduler.msCounter = 0;
    scheduler.regulatorTask = 0;
    scheduler.telemetryTask = 0;
    scheduler.measurementTask = 0;
    scheduler.prevRegulatoryTaskMsCtr = 0;
    scheduler.prevTelemetryTaskMsCtr = 0;
    scheduler.prevMeasurementTaskMsCtr = 0;
    scheduler.pSettings = &(d->settings);
    d->pSheduler = &scheduler;
}

void timerCallback()
{
    scheduler.msCounter++;
    if (scheduler.msCounter - scheduler.prevRegulatoryTaskMsCtr >= 20) {
        scheduler.regulatorTask = 1;
        scheduler.prevRegulatoryTaskMsCtr = scheduler.msCounter;
    }
    if (scheduler.msCounter - scheduler.prevTelemetryTaskMsCtr >= scheduler.pSettings->telemetryPeriod) {
        scheduler.telemetryTask = 1;
        scheduler.prevTelemetryTaskMsCtr = scheduler.msCounter;
    }
    if (scheduler.msCounter - scheduler.prevMeasurementTaskMsCtr >= 200) {
        scheduler.measurementTask = 1;
        scheduler.prevMeasurementTaskMsCtr = scheduler.msCounter;
    }
}