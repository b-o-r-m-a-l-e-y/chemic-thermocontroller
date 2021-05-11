#include "regulator.h"

void configureRegulator(struct regulator_t* r, float kI, float kP, float interval)
{
    r->kI = kI;
    r->kP = kP;
    r->interval = interval;
    r->integratedValue = 0;
    r->output = 0;
}

uint16_t updateRegulator(struct regulator_t* r, float requiredValue, float realValue)
{
    float error = requiredValue - realValue;
    float P = r->kP * error;
    r->integratedValue += ((r->kI) * (r->interval) * error);
    float outputFloat = P + r->integratedValue;
    if (outputFloat > 1.0) {
        r->output = 255;
        return r->output;
    }
    else if (outputFloat < 0) {
        r->output = 0;
        return r->output;
    }
    else {
        r->output = outputFloat * 255;
        return r->output;
    }
}