#include "stdio.h"
#include "interface.h"
#include "Arduino.h"
#include "settings.h"

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
            case 'T': {
                // Configure telemetry period
                uint16_t telemetryPeriod;
                sscanf(buffer, "-T %d", &telemetryPeriod);
                if (telemetryPeriod > 50 && telemetryPeriod < 10000) {
                    d->settings.telemetryPeriod = telemetryPeriod;
                    Serial.println("ACK");
                }
                else Serial.println("NACK");
                break;
            }
            case 't': {
                // Configure temperature
                float reqTemp;
                sscanf(buffer, "-t %f", &reqTemp);
                if (reqTemp > 1.0 && reqTemp < 200.0) {
                    d->settings.requiredTemperature = reqTemp;
                    Serial.println("ACK");
                }
                else Serial.println("NACK");
                break;
            }
            case 'o': {
                // Set temperature offset
                float temperatureOffset;
                if (sscanf(buffer, "-o %f", &temperatureOffset)) {
                    d->settings.temperatureOffset = temperatureOffset;
                    Serial.println("ACK");
                }
                else Serial.println("NACK");
                break;
            }
            case 'a':
                // Set autocontrol mode
                uint8_t mode;
                if (sscanf(buffer, "-a %u", &(mode))) {
                    d->settings.tempControlEnabled = mode;
                    Serial.println("ACK");
                }
                else Serial.println("NACK");
                break;
            case 'M': {
                // Set magnet power
                uint16_t magPower;
                if (sscanf(buffer, "-M %u", &(magPower))) {
                    if (magPower >= 0 && magPower <= 1024) {
                        d->settings.magnetPower = magPower;
                        processMagnetPower(d->settings.magnetPower);
                        Serial.println("ACK");
                    }
                    else Serial.println("NACK Bad value");
                }
                else Serial.println("NACK");
                break;
            }
            case 'q': {
                // Linear temperature interpolation mode
                uint64_t timeInMinutes = 0;
                float linearTemperature = 0;
                if (sscanf(buffer, "-q %f %d", &linearTemperature, &timeInMinutes)) {
                    // Convert minutes to ms
                    d->settings.linearTemperatureTime = timeInMinutes * 60 * 1000;
                    d->settings.linearTemperature = linearTemperature;
                    d->settings.linearTemperature0 = d->settings.requiredTemperature;
                    d->settings.linearTemperatureMsCounter = 0;
                    d->settings.linearTemperatureControlFlag = 1;
                    d->settings.tempControlEnabled = 1;
                }
                else Serial.println("NACK");
            }
            case 'p': {
                // Set P coefficient
                float pCoef;
                if (sscanf(buffer, "-p %f", &pCoef)) {
                    d->regulator.kP = pCoef;
                    Serial.println("ACK");
                }
                else Serial.println("NACK");
                break;
            }
            case 'i': {
                // Set I coefficient
                float iCoef;
                if (sscanf(buffer, "-p %f", &iCoef)) {
                    d->regulator.kI = iCoef;
                    Serial.println("ACK");
                }
                else Serial.println("NACK");
                break;
            }
            case 'g':
                sendSettings(d);
                break;
            case 's':
                // Save parameters
                saveSettingsInFlash(&(d->settings), &(d->regulator));
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

void sendSettings(struct device_t *d)
{
    char buffer[128];
    sprintf(buffer, "Period: %d\r\n", d->settings.telemetryPeriod);
    Serial.print(buffer);
    sprintf(buffer, "Mag Power: %d\r\n", d->settings.magnetPower);
    Serial.print(buffer);
    char coefS[16];
    dtostrf(d->regulator.kP, 5, 5, coefS);
    sprintf(buffer, "kP: %s\r\n", coefS);
    Serial.print(buffer);
    dtostrf(d->regulator.kI, 5, 5, coefS);
    sprintf(buffer, "kI: %s\r\n", coefS);
    Serial.print(buffer);
}