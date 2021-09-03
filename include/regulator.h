#ifndef REGULATOR_H
#define REGULATOR_H

#include "stdint.h"

#define DEFAULT_KP      0.5
#define DEFAULT_KI      0.1
#define DEFAULT_T       20

struct regulator_t
{
    float kP;
    float kI;
    float interval;
    float integratedValue;
    uint16_t output;
};

void configureRegulator(struct regulator_t*, float interval);
uint16_t updateRegulator(struct regulator_t*, float requiredValue, float realValue);

#endif