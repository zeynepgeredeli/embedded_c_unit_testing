#include <stdint.h>
#ifndef DTC_H
#define DTC_H

#define DTC_MAX_STORED     10
#define DTC_CLEARED        0x0000

typedef enum {
    DTC_OK,
    DTC_STORAGE_FULL,
    DTC_NOT_FOUND,
    DTC_ALREADY_EXISTS,
    DTC_INVALID_CODE
} DTCStatus;

typedef struct {
    uint16_t code;
    uint8_t  occurrence_count;
    uint8_t  is_active;
} DTCEntry;

typedef struct {
    DTCEntry entries[DTC_MAX_STORED];
    uint8_t  count;
} DTCStorage;

void      dtc_init(DTCStorage *storage);
DTCStatus dtc_store(DTCStorage *storage, uint16_t code);
DTCStatus dtc_clear(DTCStorage *storage, uint16_t code);
DTCStatus dtc_clear_all(DTCStorage *storage);
int       dtc_is_active(const DTCStorage *storage, uint16_t code);
uint8_t   dtc_get_count(const DTCStorage *storage);

#endif