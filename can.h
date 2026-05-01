#include <stdint.h>
#ifndef CAN_H
#define CAN_H

#define CAN_MAX_DLC        8
#define CAN_MAX_ID         0x7FF    // 11-bit max
#define CAN_MIN_ID         0x000

typedef enum {
    CAN_OK,
    CAN_INVALID_ID,
    CAN_INVALID_DLC,
    CAN_CHECKSUM_ERROR,
    CAN_NULL_POINTER
} CANStatus;

typedef struct {
    uint32_t id;
    uint8_t  dlc;
    uint8_t  data[CAN_MAX_DLC];
    uint8_t  checksum;
} CANFrame;

CANStatus validate_can_frame(const CANFrame *frame);
uint8_t   calculate_checksum(const CANFrame *frame);

#endif