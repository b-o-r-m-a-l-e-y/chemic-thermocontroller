#include "dimmer.h"
#include "Arduino.h"
#include "board.h"

void configureDimmer(struct dimmerConf_t* d)
{
    d->halfPeriodCtr = 0;
    d->requriedPowerValue = 0;
    d->lastIdealValue = 0;
    d->lastPinState = 0;
}

/*
 * Function implements Bresenham`s algorithm
 * to either turn on/off GPIO pin. 
 */
void processDimmerMeasurements(struct dimmerConf_t* d)
{
    // Simply y = k*x, where k = ctr/255
    uint16_t idealValue = ((d->halfPeriodCtr * d->requriedPowerValue) >> 8);
    uint8_t pinState = d->lastIdealValue != idealValue;
    // Really we need this if?
    //if (d->lastPinState != pinState)
    if (d->requriedPowerValue == 0) digitalWrite(HEATERS_PIN, 0);
    else if (d->requriedPowerValue == 1) digitalWrite(HEATERS_PIN, 1);
    else digitalWrite(HEATERS_PIN, pinState);
    //d->lastPinState = pinState;
    d->lastIdealValue = idealValue;
    d->halfPeriodCtr++;
}