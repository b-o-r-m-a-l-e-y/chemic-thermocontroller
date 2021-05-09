#include "stdio.h"
#include "interface.h"
#include "Arduino.h"

void processSerial(struct device_t* d)
{
    if(Serial.available())
    {
        char buffer[64];
        Serial.readBytesUntil('\r',(uint8_t*) buffer, 64);
        if (buffer[0] == '-')
        {
            switch(buffer[1])
            {
            case 'T':
                // Configure telemetry period
                break;
            case 't':
                // Configure temperature
                break;
            case 'a':
                // Set autocontrol mode
                break;
            case 'M':
                // Set magnet power
                break;
            case 'p':
                // Set P coefficient
                break;
            case 'i':
                // Set I coefficient
                break;
            case 's':
                // Save parameters
                Serial.println("ACK");
                break;
            default:
                Serial.println("NACK");
            }
        }
    }
}

void sendTelemetry(struct device_t* d)
{
    char buffer[128];
    char thermopairTempS[10];
    char internalTemp[10];
    dtostrf(d->actualTemperature, 5, 2, thermopairTempS);
    dtostrf(d->internalTemperature, 5, 2, internalTemp);
    sprintf(buffer, "Ta: %s Ti: %s\r\n", thermopairTempS, internalTemp);
    Serial.print(buffer);
}