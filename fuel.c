#include "fuel.h"

#define TANK_CAPACITY_LITERS  80

FuelStatus check_fuel_level(int fuel_percentage) {
    FuelStatus status = FUEL_NORMAL;

    if ((fuel_percentage < 0) || (fuel_percentage > 100)) {
        status = FUEL_SENSOR_FAULT;
    } else if (fuel_percentage == 0) {
        status = FUEL_EMPTY;
    } else if (fuel_percentage <= 10) {
        status = FUEL_CRITICAL;
    } else if (fuel_percentage <= 25) {
        status = FUEL_LOW;
    } else {
        status = FUEL_NORMAL;
    }

    return status;
}

int get_estimated_range(int fuel_percentage, int consumption_per_100km) {
    int range = -1;
    int fuel_liters = 0;

    if ((fuel_percentage < 0) || (fuel_percentage > 100)) {
        range = -1;
    } else if (consumption_per_100km <= 0) {
        range = -1;
    } else {
        fuel_liters = TANK_CAPACITY_LITERS * fuel_percentage / 100;
        range = fuel_liters * 100 / consumption_per_100km;
    }

    return range;
}