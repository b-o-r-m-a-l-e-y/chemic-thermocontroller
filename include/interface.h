#ifndef INTERFACE_H
#define INTERFACE_H

#include "device.h"

void processSerial();
void sendTelemetry(struct device_t*);

#endif