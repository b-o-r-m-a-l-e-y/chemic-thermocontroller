#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "board.h"
#include "device.h"
#include "interface.h"
#include "TimerOne.h"

struct device_t device;

void setup() {
}

void loop() {
    configureDevice(&device);
    uint32_t prevTime = 0;
    uint32_t prevTimeDimmer = 0;
    device.dimmer.requriedPowerValue = 32;
    Timer1.initialize(1000);
    Timer1.attachInterrupt(timerCallback);
    Timer1.start();
    while(1)
    {
        temperatureMeasurement(&device);
        processSerial(&device);
        if (millis() - prevTime >= device.settings.telemetryPeriod)
        {
            sendTelemetry(&device);
            prevTime = millis();
        }
        if (millis() - prevTimeDimmer >= 10)
        {
            processDimmerMeasurements(&(device.dimmer));
        }
    }
}