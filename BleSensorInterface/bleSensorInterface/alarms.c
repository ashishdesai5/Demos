/**
 * @file
 *
 * <HR>
 *
 * Copyright (C) Sierra Wireless, Inc. Use of this work is subject to license.
 */

#include "legato.h"
#include "interfaces.h"

#define TIME_NOW (time(NULL))

#define ALARM_SHOCK_VAL           (1.0)
#define ALARM_TEMPERATURE_ON_VAL  (31.0)
#define ALARM_TEMPERATURE_OFF_VAL (30.0)
#define ALARM_HUMIDITY_ON_VAL     (45.0)
#define ALARM_HUMIDITY_OFF_VAL    (40.0)
#define ALARM_LUMINOSITY_ON_VAL   (50.0)
#define ALARM_LUMINOSITY_OFF_VAL  (40.0)


// Data to publish
const char* alarmShockKey       = "a.bt.alarm.shock";
const char* alarmTemperatureKey = "a.bt.alarm.temperature";
const char* alarmHumidityKey    = "a.bt.alarm.humidity";
const char* alarmLuminosityKey  = "a.bt.alarm.luminosity";
const char* alarmOrientationKey = "a.bt.alarm.orientation";

void checkShockAlarm(double shockValue)
{
    if (shockValue > ALARM_SHOCK_VAL)
    {
        dataRouter_WriteFloat(alarmShockKey, shockValue, TIME_NOW);
    }
}

void checkTemperatureAlarm(double temperature)
{
    static bool alarmOn = false;
    static bool anyUpdateReceived = false;

    if ((!alarmOn || !anyUpdateReceived) && temperature > ALARM_TEMPERATURE_ON_VAL)
    {
        alarmOn = true;
        dataRouter_WriteBoolean(alarmTemperatureKey, alarmOn, TIME_NOW);
    }
    else if (alarmOn && temperature < ALARM_TEMPERATURE_OFF_VAL)
    {
        alarmOn = false;
        dataRouter_WriteBoolean(alarmTemperatureKey, alarmOn, TIME_NOW);
    }
    anyUpdateReceived = true;
}

void checkHumidityAlarm(double humidity)
{
    static bool alarmOn = false;
    static bool anyUpdateReceived = false;

    if ((!alarmOn || !anyUpdateReceived) && humidity > ALARM_HUMIDITY_ON_VAL)
    {
        alarmOn = true;
        dataRouter_WriteBoolean(alarmHumidityKey, alarmOn, TIME_NOW);
    }
    else if (alarmOn && humidity < ALARM_HUMIDITY_OFF_VAL)
    {
        alarmOn = false;
        dataRouter_WriteBoolean(alarmHumidityKey, alarmOn, TIME_NOW);
    }
    anyUpdateReceived = true;
}

void checkLuminosityAlarm(double luminosity)
{
    static bool alarmOn = false;
    static bool anyUpdateReceived = false;

    if ((!alarmOn || !anyUpdateReceived) && luminosity > ALARM_LUMINOSITY_ON_VAL)
    {
        alarmOn = true;
        dataRouter_WriteBoolean(alarmLuminosityKey, alarmOn, TIME_NOW);
    }
    else if (alarmOn && luminosity < ALARM_LUMINOSITY_OFF_VAL)
    {
        alarmOn = false;
        dataRouter_WriteBoolean(alarmLuminosityKey, alarmOn, TIME_NOW);
    }
    anyUpdateReceived = true;
}

void checkOrientationAlarm(int32_t orientation)
{
    static bool alarmOn = false;
    static bool anyUpdateReceived = false;

    const int32_t upright = 5;
    bool newAlarmOn = orientation != upright;
    if (!anyUpdateReceived || newAlarmOn != alarmOn)
    {
        alarmOn = newAlarmOn;
        anyUpdateReceived = true;
        dataRouter_WriteBoolean(alarmOrientationKey, newAlarmOn, TIME_NOW);
    }
}
