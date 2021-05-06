#ifndef SETTINGS_H
#define SETTINGS_H

#include "stdint.h"

struct settings_t
{
    uint16_t    telemetryPeriod;
    float       requiredTemperature;
    uint8_t     tempControlEnabled;
    uint8_t     magnetPower;
    // PI coefficients
};

struct settingsFlash_t
{
    uint16_t    telemetryPeriod;
    uint16_t    crc16;
};

extern settings_t settings;

void loadDefaultSettings(struct settings_t*);
void saveSettingsInFlash(struct settings_t*);

#endif