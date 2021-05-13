#include "scheduler.h"

// Sorry for this, but in current realization
// I couldn`t pass a parameter to timerCallback.
// Really need to reimplement this
struct scheduler_t scheduler;

void configureScheduler(struct settings_t* s, struct scheduler_t* pSheduler)
{
    scheduler.msCounter = 0;
    scheduler.regulatorTask = 0;
    scheduler.telemetryTask = 0;
    scheduler.prevRegulatoryTaskMsCtr = 0;
    scheduler.prevTelemetryTaskMsCtr = 0;
    pSheduler = &scheduler;
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
}