#include "can.h"

uint8_t calculate_checksum(const CANFrame *frame) {
    uint8_t sum = 0;
    int i;
    for (i = 0; i < frame->dlc; i++) {
        sum += frame->data[i];
    }
    return sum;
}

CANStatus validate_can_frame(const CANFrame *frame) {
    if (frame == NULL) {
        return CAN_NULL_POINTER;
    }
    if (frame->id > CAN_MAX_ID) {
        return CAN_INVALID_ID;
    }
    if (frame->dlc > CAN_MAX_DLC) {
        return CAN_INVALID_DLC;
    }
    if (frame->dlc > 0) {
        if (calculate_checksum(frame) != frame->checksum) {
            return CAN_CHECKSUM_ERROR;
        }
    }
    return CAN_OK;
}