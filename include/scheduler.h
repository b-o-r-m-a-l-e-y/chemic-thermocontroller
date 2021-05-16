#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "stdint.h"
#include "settings.h"

struct scheduler_t
{
    uint8_t regulatorTask   : 1;
    uint8_t telemetryTask   : 1;
    uint8_t measurementTask : 1;
    uint8_t reserved        : 5;
    uint64_t msCounter;
    uint64_t prevRegulatoryTaskMsCtr;
    uint64_t prevTelemetryTaskMsCtr;
    uint64_t prevMeasurementTaskMsCtr;
    struct settings_t* pSettings;
};

void configureScheduler(struct settings_t*, struct scheduler_t*);
void timerCallback();

#endif