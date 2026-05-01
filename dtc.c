#include "dtc.h"

void dtc_init(DTCStorage *storage) {
    uint8_t i;
    storage->count = 0;
    for (i = 0; i < DTC_MAX_STORED; i++) {
        storage->entries[i].code = DTC_CLEARED;
        storage->entries[i].occurrence_count = 0;
        storage->entries[i].is_active = 0;
    }
}

DTCStatus dtc_store(DTCStorage *storage, uint16_t code) {
    uint8_t i;

    if (code == DTC_CLEARED) {
        return DTC_INVALID_CODE;
    }

    // check if already exists
    for (i = 0; i < storage->count; i++) {
        if (storage->entries[i].code == code) {
            storage->entries[i].occurrence_count++;
            storage->entries[i].is_active = 1;
            return DTC_ALREADY_EXISTS;
        }
    }

    // check if storage is full
    if (storage->count >= DTC_MAX_STORED) {
        return DTC_STORAGE_FULL;
    }

    // store new DTC
    storage->entries[storage->count].code = code;
    storage->entries[storage->count].occurrence_count = 1;
    storage->entries[storage->count].is_active = 1;
    storage->count++;

    return DTC_OK;
}

DTCStatus dtc_clear(DTCStorage *storage, uint16_t code) {
    uint8_t i;
    for (i = 0; i < storage->count; i++) {
        if (storage->entries[i].code == code) {
            storage->entries[i].is_active = 0;
            storage->entries[i].code = DTC_CLEARED;
            storage->count--;
            return DTC_OK;
        }
    }
    return DTC_NOT_FOUND;
}

DTCStatus dtc_clear_all(DTCStorage *storage) {
    dtc_init(storage);
    return DTC_OK;
}

int dtc_is_active(const DTCStorage *storage, uint16_t code) {
    uint8_t i;
    for (i = 0; i < storage->count; i++) {
        if (storage->entries[i].code == code &&
            storage->entries[i].is_active == 1) {
            return 1;
        }
    }
    return 0;
}

uint8_t dtc_get_count(const DTCStorage *storage) {
    return storage->count;
}