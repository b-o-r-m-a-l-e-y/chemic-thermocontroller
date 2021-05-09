#ifndef DEVICE_H
#define DEVICE_H

#include "settings.h"
#include "board.h"
#include "Adafruit_MAX31855.h"

struct device_t
{
    settings_t  settings;
    float      actualTemperature;
    float      internalTemperature;
    uint8_t     flagsThermocouple;
    float      magnetTemperature;
};

void configureDevice(struct device_t*);
void temperatureMeasurement(struct device_t*);
void processThermocontrol(struct device_t*);

#endif