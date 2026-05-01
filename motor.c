#include "motor.h"

MotorStatus check_motor_temperature(int temperature) {
    MotorStatus status = NORMAL;

    if (temperature < -40) {
        status = SENSOR_FAULT;
    } else if (temperature > 150) {
        status = SENSOR_FAULT;
    } else if (temperature >= 120) {
        status = EMERGENCY;
    } else if (temperature >= 105) {
        status = CRITICAL_WARNING;
    } else if (temperature >= 90) {
        status = WARNING;
    } else {
        status = NORMAL;
    }

    return status;
}

int apply_power_restriction(MotorStatus status) {
    int power = 100;

    if (status == EMERGENCY) {
        power = 50;
    } else if (status == CRITICAL_WARNING) {
        power = 80;
    } else {
        power = 100;
    }

    return power;
}