#ifndef DIMMER_H
#define DIMMER_H

#include "stdint.h"

/*
 * Dimmer realization with contolling load by
 * turning it on and off on several half-periods of
 * 50 Hz sine wave. Should be used triac optorelay,
 * with integrated zero detection.
 * No external zero detection circuit needed.
 */

#define NUM_OF_HALF_PERIODS

struct dimmerConf_t
{
    uint8_t requriedPowerValue;
    uint8_t halfPeriodCtr;
    uint16_t lastIdealValue;
    uint8_t lastPinState;
};

void configureDimmer(struct dimmerConf_t*);

/*
 * Should be used with 10 ms time quant
 * (every half period of 50 Hz)
 */
void processDimmerMeasurements(struct dimmerConf_t*);

#endif