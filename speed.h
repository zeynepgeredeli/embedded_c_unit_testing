#ifndef SPEED_H
#define SPEED_H

typedef enum {
    SPEED_NORMAL,
    SPEED_WARNING,
    SPEED_LIMIT_EXCEEDED,
    SPEED_CRITICAL,
    SPEED_SENSOR_FAULT
} SpeedStatus;

SpeedStatus check_speed_limit(int current_speed, int speed_limit);
int apply_speed_warning(SpeedStatus status);

#endif