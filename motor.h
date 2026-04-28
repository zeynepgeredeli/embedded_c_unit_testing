
#ifndef MOTOR_H
#define MOTOR_H

typedef enum {
    NORMAL,
    WARNING,
    CRITICAL_WARNING,
    EMERGENCY,
    SENSOR_FAULT
} MotorStatus;

MotorStatus check_motor_temperature(int temperature);
int apply_power_restriction(MotorStatus status);

#endif