#ifndef DEVICE_H
#define DEVICE_H

#include "settings.h"
#include "dimmer.h"
#include "board.h"
#include "Wire.h"
#include "SPI.h"
#include "Adafruit_MAX31855.h"
#include "scheduler.h"
#include "regulator.h"

struct device_t
{
    struct settings_t settings;
    struct dimmerConf_t dimmer;
    struct regulator_t regulator;
    struct scheduler_t* pSheduler; 
    float      actualTemperature;
    float      internalTemperature;
    uint8_t     flagsThermocouple;
    float      magnetTemperature;
};

void configureDevice(struct device_t*);
void temperatureMeasurement(struct device_t*);
void mainLoop(struct device_t* d);

#endif