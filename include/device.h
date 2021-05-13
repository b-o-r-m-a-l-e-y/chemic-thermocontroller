#ifndef DEVICE_H
#define DEVICE_H

#include "settings.h"
#include "dimmer.h"
#include "board.h"
#include "Adafruit_MAX31855.h"
#include "scheduler.h"

struct device_t
{
    struct settings_t settings;
    struct dimmerConf_t dimmer;
    struct scheduler_t* pSheduler; 
    float      actualTemperature;
    float      internalTemperature;
    uint8_t     flagsThermocouple;
    float      magnetTemperature;
};

void configureDevice(struct device_t*);
void temperatureMeasurement(struct device_t*);
void processThermocontrol(struct device_t*);

#endif