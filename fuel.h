#ifndef FUEL_H
#define FUEL_H

typedef enum {
    FUEL_NORMAL,
    FUEL_LOW,
    FUEL_CRITICAL,
    FUEL_EMPTY,
    FUEL_SENSOR_FAULT
} FuelStatus;

FuelStatus check_fuel_level(int fuel_percentage);
int get_estimated_range(int fuel_percentage, int consumption_per_100km);

#endif