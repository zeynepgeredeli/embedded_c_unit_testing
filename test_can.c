#include <stdio.h>
#include "can.h"

int passed = 0;
int failed = 0;

void check(const char *test_name, int result, int expected) {
    if (result == expected) {
        printf("PASS: %s\n", test_name);
        passed++;
    } else {
        printf("FAIL: %s | expected: %d | got: %d\n", test_name, expected, result);
        failed++;
    }
}

int main() {
    printf("=== CAN Frame Validation Tests ===\n\n");

    CANFrame valid_frame = {
        .id = 0x100,
        .dlc = 3,
        .data = {0x01, 0x02, 0x03, 0, 0, 0, 0, 0},
        .checksum = 0x06
    };
    check("Valid CAN frame",validate_can_frame(&valid_frame), CAN_OK);

    CANFrame invalid_id_frame = {
        .id = 0x800,
        .dlc = 2,
        .data = {0x01, 0x02, 0, 0, 0, 0, 0, 0},
        .checksum = 0x03
    };
    check("Invalid ID (over 0x7FF)",validate_can_frame(&invalid_id_frame), CAN_INVALID_ID);

    CANFrame invalid_dlc_frame = {
        .id = 0x200,
        .dlc = 9,
        .data = {0x01, 0, 0, 0, 0, 0, 0, 0},
        .checksum = 0x01
    };
    check("Invalid DLC (over 8)",validate_can_frame(&invalid_dlc_frame), CAN_INVALID_DLC);

    CANFrame bad_checksum_frame = {
        .id = 0x300,
        .dlc = 2,
        .data = {0x10, 0x20, 0, 0, 0, 0, 0, 0},
        .checksum = 0xFF
    };
    check("Checksum mismatch",validate_can_frame(&bad_checksum_frame), CAN_CHECKSUM_ERROR);

    check("NULL pointer",validate_can_frame(NULL), CAN_NULL_POINTER);

    CANFrame empty_frame = {
        .id = 0x400,
        .dlc = 0,
        .data = {0, 0, 0, 0, 0, 0, 0, 0},
        .checksum = 0x00
    };
    check("Empty frame (DLC 0)",validate_can_frame(&empty_frame), CAN_OK);

    CANFrame max_id_frame = {
        .id = 0x7FF,
        .dlc = 1,
        .data = {0xAB, 0, 0, 0, 0, 0, 0, 0},
        .checksum = 0xAB
    };
    check("Max valid ID (0x7FF)",validate_can_frame(&max_id_frame), CAN_OK);

    CANFrame full_frame = {
        .id = 0x500,
        .dlc = 8,
        .data = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08},
        .checksum = 0x24
    };
    check("Full frame (DLC 8)",validate_can_frame(&full_frame), CAN_OK);

    printf("\n=== Result: %d PASS, %d FAIL ===\n", passed, failed);
    return failed;
}