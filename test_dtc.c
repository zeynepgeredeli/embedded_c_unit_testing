#include <stdio.h>
#include "dtc.h"

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
    printf("=== DTC Management Unit Tests ===\n\n");

    DTCStorage storage;
    dtc_init(&storage);

    // init test
    check("Storage initialized empty",dtc_get_count(&storage), 0);

    // store single DTC
    check("Store valid DTC P0115",dtc_store(&storage, 0x0115), DTC_OK);

    check("Count after first store",dtc_get_count(&storage), 1);

    // DTC is active
    check("DTC P0115 is active",dtc_is_active(&storage, 0x0115), 1);

    // store duplicate
    check("Store duplicate DTC",dtc_store(&storage, 0x0115), DTC_ALREADY_EXISTS);

    check("Count unchanged after duplicate",dtc_get_count(&storage), 1);

    // store more DTCs
    dtc_store(&storage, 0x0217);
    dtc_store(&storage, 0x0100);
    check("Count after 3 unique DTCs",dtc_get_count(&storage), 3);

    // clear single DTC
    check("Clear existing DTC",dtc_clear(&storage, 0x0115), DTC_OK);

    check("DTC P0115 no longer active",dtc_is_active(&storage, 0x0115), 0);

    check("Count after clear",dtc_get_count(&storage), 2);

    // clear non-existing DTC
    check("Clear non-existing DTC",dtc_clear(&storage, 0x9999), DTC_NOT_FOUND);

    // invalid code
    check("Store invalid code 0x0000",dtc_store(&storage, 0x0000), DTC_INVALID_CODE);

    // fill storage
    dtc_clear_all(&storage);
    uint8_t i;
    for (i = 0; i < DTC_MAX_STORED; i++) {
        dtc_store(&storage, 0x0100 + i);
    }
    check("Storage full",dtc_store(&storage, 0x0999), DTC_STORAGE_FULL);

    // clear all
    check("Clear all DTCs",dtc_clear_all(&storage), DTC_OK);

    check("Count after clear all",dtc_get_count(&storage), 0);

    printf("\n=== Result: %d PASS, %d FAIL ===\n", passed, failed);
    return failed;
}