#include "settings.h"

void loadDefaultSettings(struct settings_t* s)
{
    s->magnetPower = 0;
    s->telemetryPeriod = 1000;
    s->tempControlEnabled = 0;
    s->requiredTemperature = 20.0;
    s->temperatureOffset = 0.0;
}