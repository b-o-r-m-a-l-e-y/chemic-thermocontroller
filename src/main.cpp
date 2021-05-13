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
    while(1)
    {
        temperatureMeasurement(&device);
        processSerial(&device);
        if (device.pSheduler->telemetryTask) sendTelemetry(&device);
        if (device.pSheduler->regulatorTask) processDimmerMeasurements(&(device.dimmer));
    }
}