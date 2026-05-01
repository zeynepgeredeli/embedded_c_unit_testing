# Embedded C Unit Testing

## Modules

### Motor Temperature Monitor
Monitors engine temperature and applies power restrictions to prevent motor damage.

### Speed Limit Controller
Validates vehicle speed according to defined limits and generates warnings.
Handles sensor fault detection for unrealistic speed values.

### Fuel Level Manager
Monitors fuel percentage and estimates remaining range based on consumption.

### CAN Frame Validator
Validates CAN 2.0A frames (11-bit ID) including ID range, DLC bounds,
and checksum verification. Handles null pointer and empty frame edge cases.

### DTC Manager
Implements a Diagnostic Trouble Code storage system supporting up to 10 
concurrent fault codes. Supports store, clear, and query operations matching 
OBD-II diagnostic workflows.

## Test Coverage
Motor  **16**   PASS 
Speed  **13**   PASS 
Fuel   **13**   PASS 
CAN    **8**    PASS 
DTC    **15**   PASS 
Total  **65**   All Pass 

## MISRA C Compliance

All modules follow key MISRA C guidelines:
- Single point of exit per function 
- Unsigned integer literals use U suffix 
- All if-else blocks use braces 
- Variables initialized before use 
- Null pointer checks before dereference

## CI/CD

This project uses GitHub Actions for automated build and test on every push.

## Build & Run

# All tests
gcc motor.c speed.c fuel.c dtc.c can.c test.c -o test_runner 
./test_runner

# CAN tests
gcc can.c test_can.c -o test_can 
./test_can

# DTC tests
gcc dtc.c test_dtc.c -o test_dtc 
./test_dtc