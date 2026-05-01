#include "dtc.h"

void dtc_init(DTCStorage *storage) {
    uint8_t i = 0U;

    storage->count = 0U;
    for (i = 0U; i < DTC_MAX_STORED; i++) {
        storage->entries[i].code = DTC_CLEARED;
        storage->entries[i].occurrence_count = 0U;
        storage->entries[i].is_active = 0U;
    }
}

DTCStatus dtc_store(DTCStorage *storage, uint16_t code) {
    DTCStatus status = DTC_OK;
    uint8_t i = 0U;
    uint8_t found = 0U;

    if (code == DTC_CLEARED) {
        status = DTC_INVALID_CODE;
    } else {
        for (i = 0U; i < storage->count; i++) {
            if (storage->entries[i].code == code) {
                storage->entries[i].occurrence_count++;
                storage->entries[i].is_active = 1U;
                status = DTC_ALREADY_EXISTS;
                found = 1U;
            }
        }

        if (found == 0U) {
            if (storage->count >= DTC_MAX_STORED) {
                status = DTC_STORAGE_FULL;
            } else {
                storage->entries[storage->count].code = code;
                storage->entries[storage->count].occurrence_count = 1U;
                storage->entries[storage->count].is_active = 1U;
                storage->count++;
                status = DTC_OK;
            }
        }
    }

    return status;
}

DTCStatus dtc_clear(DTCStorage *storage, uint16_t code) {
    DTCStatus status = DTC_NOT_FOUND;
    uint8_t i = 0U;

    for (i = 0U; i < storage->count; i++) {
        if (storage->entries[i].code == code) {
            storage->entries[i].is_active = 0U;
            storage->entries[i].code = DTC_CLEARED;
            storage->count--;
            status = DTC_OK;
        }
    }

    return status;
}

DTCStatus dtc_clear_all(DTCStorage *storage) {
    dtc_init(storage);
    return DTC_OK;
}

int dtc_is_active(const DTCStorage *storage, uint16_t code) {
    int result = 0;
    uint8_t i = 0U;

    for (i = 0U; i < storage->count; i++) {
        if ((storage->entries[i].code == code) &&
            (storage->entries[i].is_active == 1U)) {
            result = 1;
        }
    }

    return result;
}

uint8_t dtc_get_count(const DTCStorage *storage) {
    return storage->count;
}