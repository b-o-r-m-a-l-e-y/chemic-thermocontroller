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
    if ((!isnan(requiredValue)) && (!isnan(realValue))) {
        float error = requiredValue - realValue;
        float P = r->kP * error;
        r->integratedValue += ((r->kI) * (r->interval) * error);
        float outputFloat = P + r->integratedValue;
        char buffer[128];
        char errFloat[10];
        char outFloatS[10];
        char integratedValueS[10];
        dtostrf(error, 5, 2, errFloat);
        dtostrf(outputFloat, 5, 2, outFloatS);
        dtostrf(r->integratedValue, 5, 2, integratedValueS);
        sprintf(buffer, "Err: %s Out: %s Int: %s\r\n", errFloat, outFloatS, integratedValueS);
        Serial.print(buffer);
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
}