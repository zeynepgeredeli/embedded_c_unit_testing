#include "motor.h"

// the temperature values are provided as example values 
MotorStatus check_motor_temperature(int temperature) {
    if (temperature < -40 || temperature > 150) {
        return SENSOR_FAULT;
    }
    if (temperature >= 120) {
        return EMERGENCY;
    }
    if (temperature >= 105) {
        return CRITICAL_WARNING;
    }
    if (temperature >= 90) {
        return WARNING;
    }
    return NORMAL;
}

int apply_power_restriction(MotorStatus status) {
    if (status == EMERGENCY) {
        return 50; // power that goes to the motor (percentage %)
    }
    if (status == CRITICAL_WARNING) {
        return 80;
    }
    return 100;
}

