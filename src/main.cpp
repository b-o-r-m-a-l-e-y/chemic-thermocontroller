#include <Arduino.h>
#include "device.h"

struct device_t device;

void setup() {
}

void loop() {
    configureDevice(&device);
    mainLoop(&device);
}