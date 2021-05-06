#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "board.h"
#include "device.h"
#include "interface.h"

struct device_t device;

void setup() {
}

void loop() {
    configureDevice(&device);
    uint32_t prevTime = 0;
    while(1)
    {
        temperatureMeasurement(&device);
        processSerial();
        if (millis() - prevTime >= device.settings.telemetryPeriod)
        {
            sendTelemetry(&device);
            prevTime = millis();
        }
        delay(10);
    }
}