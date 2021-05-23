#ifndef INTERFACE_H
#define INTERFACE_H

#include "device.h"

void processSerial(struct device_t*);
void sendTelemetry(struct device_t*);
void sendSettings(struct device_t*);

#endif