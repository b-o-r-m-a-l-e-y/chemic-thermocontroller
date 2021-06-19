#ifndef SETTINGS_H
#define SETTINGS_H

#include "stdint.h"
#include "regulator.h"

struct settings_t
{
    uint16_t    telemetryPeriod;
    float       requiredTemperature;
    uint8_t     tempControlEnabled;
    uint16_t    magnetPower;
    float       temperatureOffset;
    uint8_t     linearTemperatureControlFlag;
    uint64_t    linearTemperatureTime;
    uint64_t    linearTemperatureMsCounter;
    float       linearTemperature;
    float       linearTemperature0;
};

struct settingsFlash_t
{
    uint16_t    telemetryPeriod;
    float       kI;
    float       kP;
    float       temperatureOffset;
    uint16_t    crc8;
};

void loadDefaultSettings(struct settings_t*, struct regulator_t*);
void loadSettingsFromFlash(struct settings_t*, struct regulator_t*);
void saveSettingsInFlash(struct settings_t*, struct regulator_t*);

#endif