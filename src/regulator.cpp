#include "regulator.h"
#include "Arduino.h"

void configureRegulator(struct regulator_t* r, float interval)
{
    r->interval = interval;
    r->integratedValue = 0;
    r->output = 0;
}

uint8_t updateRegulator(struct regulator_t* r, float requiredValue, float realValue)
{
    const float INTEGRAL_SATURATION = 1000.0;
    const float NORMALIZATION = 1.0;
    const float MAX_TEMP = 300.0;
    if ((!isnan(requiredValue)) && (!isnan(realValue))) {
        float error = (requiredValue - realValue) / MAX_TEMP;
        float P = r->kP * error;
        r->integratedValue += ((r->kI) * (r->interval) * error);
        if (r->integratedValue > INTEGRAL_SATURATION) r->integratedValue = INTEGRAL_SATURATION;
        else if (r->integratedValue < -INTEGRAL_SATURATION) r->integratedValue = -INTEGRAL_SATURATION;
        float outputFloat = (P + r->integratedValue) / NORMALIZATION;
        char buffer[128];
        char tempErr[10];
        char errFloat[10];
        char outFloatS[10];
        char integratedValueS[10];
        dtostrf(requiredValue - realValue, 4, 4, tempErr);
        dtostrf(error, 4, 4, errFloat);
        dtostrf(outputFloat, 4, 4, outFloatS);
        dtostrf(r->integratedValue, 4, 4, integratedValueS);
        sprintf(buffer, "Err_t: %s Err_f: %s Out: %s Int: %s\r\n", tempErr, errFloat, outFloatS, integratedValueS);
        Serial.print(buffer);
        if (outputFloat > 1.0) r->output = 255;
        else if (outputFloat < 0) r->output = 0;
        else r->output = outputFloat * 255;
        sprintf(buffer, "Dim: %d\r\n", r->output);
        Serial.print(buffer);
        return r->output;
    }
}