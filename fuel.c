#include "fuel.h"

FuelStatus check_fuel_level(int fuel_percentage) {
    if (fuel_percentage < 0 || fuel_percentage > 100) {
        return FUEL_SENSOR_FAULT;
    }
    if (fuel_percentage == 0) {
        return FUEL_EMPTY;
    }
    if (fuel_percentage <= 10) {
        return FUEL_CRITICAL;
    }
    if (fuel_percentage <= 25) {
        return FUEL_LOW;
    }
    return FUEL_NORMAL;
}

int get_estimated_range(int fuel_percentage, int consumption_per_100km) {
    if (fuel_percentage < 0 || fuel_percentage > 100) {
        return -1;
    }
    if (consumption_per_100km <= 0) {
        return -1;
    }
    // tank capacity assumed 80 liters
    int fuel_liters = 80 * fuel_percentage / 100;
    return fuel_liters * 100 / consumption_per_100km;
}