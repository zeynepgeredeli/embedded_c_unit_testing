#include "speed.h"

SpeedStatus check_speed_limit(int current_speed, int speed_limit) {
    SpeedStatus status = SPEED_NORMAL;

    if ((current_speed < 0) || (current_speed > 300)) {
        status = SPEED_SENSOR_FAULT;
    } else if (speed_limit <= 0) {
        status = SPEED_SENSOR_FAULT;
    } else if (current_speed >= (speed_limit + 50)) {
        status = SPEED_CRITICAL;
    } else if (current_speed >= (speed_limit + 20)) {
        status = SPEED_LIMIT_EXCEEDED;
    } else if (current_speed >= speed_limit) {
        status = SPEED_WARNING;
    } else {
        status = SPEED_NORMAL;
    }

    return status;
}

int apply_speed_warning(SpeedStatus status) {
    int warning_level = 0;

    if (status == SPEED_CRITICAL) {
        warning_level = 3;
    } else if (status == SPEED_LIMIT_EXCEEDED) {
        warning_level = 2;
    } else if (status == SPEED_WARNING) {
        warning_level = 1;
    } else {
        warning_level = 0;
    }

    return warning_level;
}