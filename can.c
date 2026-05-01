#include "can.h"
#include <stddef.h>


uint8_t calculate_checksum(const CANFrame *frame) {
    uint8_t sum = 0U;
    uint8_t i = 0U;

    for (i = 0U; i < frame->dlc; i++) {
        sum += frame->data[i];
    }

    return sum;
}

CANStatus validate_can_frame(const CANFrame *frame) {
    CANStatus status = CAN_OK;

    if (frame == NULL) {
        status = CAN_NULL_POINTER;
    } else if (frame->id > CAN_MAX_ID) {
        status = CAN_INVALID_ID;
    } else if (frame->dlc > CAN_MAX_DLC) {
        status = CAN_INVALID_DLC;
    } else if (frame->dlc > 0U) {
        if (calculate_checksum(frame) != frame->checksum) {
            status = CAN_CHECKSUM_ERROR;
        }
    } else {
        status = CAN_OK;
    }

    return status;
}