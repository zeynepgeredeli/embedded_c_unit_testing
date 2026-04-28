#include "speed.h"

SpeedStatus check_speed_limit(int current_speed, int speed_limit) {
    if (current_speed < 0 || current_speed > 300) {
        return SPEED_SENSOR_FAULT;
    }
    if (speed_limit <= 0) {
        return SPEED_SENSOR_FAULT;
    }
    if (current_speed >= speed_limit + 50) {
        return SPEED_CRITICAL;
    }
    if (current_speed >= speed_limit + 20) {
        return SPEED_LIMIT_EXCEEDED;
    }
    if (current_speed >= speed_limit) {
        return SPEED_WARNING;
    }
    return SPEED_NORMAL;
}

int apply_speed_warning(SpeedStatus status) {
    if (status == SPEED_CRITICAL) {
        return 3;  // urgent audio + visual warning
    }
    if (status == SPEED_LIMIT_EXCEEDED) {
        return 2;  // visual warning
    }
    if (status == SPEED_WARNING) {
        return 1;  // soft warning
    }
    return 0;  // no warning
}