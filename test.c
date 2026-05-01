#include <stdio.h>
#include "motor.h"
#include "speed.h"
#include "fuel.h"


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
    printf("=== Motor Temperature Unit Tests ===\n\n");

    // Normal range tests
    check("Normal temperature (75C)",check_motor_temperature(75), NORMAL);

    check("Normal temperature (0C)",check_motor_temperature(0), NORMAL);

    // Warning range tests
    check("Warning threshold (90C)",check_motor_temperature(90), WARNING);

    check("Warning range (100C)",check_motor_temperature(100), WARNING);

    // Critical warning tests
    check("Critical warning threshold (105C)",check_motor_temperature(105), CRITICAL_WARNING);

    check("Critical warning range (115C)",check_motor_temperature(115), CRITICAL_WARNING);

    // Emergency tests
    check("Emergency threshold (120C)",check_motor_temperature(120), EMERGENCY);

    check("Emergency range (135C)",check_motor_temperature(135), EMERGENCY);

    // Sensor fault tests
    check("Sensor fault - too cold (-41C)",check_motor_temperature(-41), SENSOR_FAULT);

    check("Sensor fault - too hot (151C)",check_motor_temperature(151), SENSOR_FAULT);

    check("Boundary - minimum valid (-40C)",check_motor_temperature(-40), NORMAL);

    check("Boundary - maximum valid (150C)",check_motor_temperature(150), EMERGENCY);

    printf("\n--- Power Restriction Tests ---\n\n");

    // Power restriction tests
    check("Normal - full power",apply_power_restriction(NORMAL), 100);

    check("Warning - full power",apply_power_restriction(WARNING), 100);

    check("Critical - 80 percent power",apply_power_restriction(CRITICAL_WARNING), 80);

    check("Emergency - 50 percent power",apply_power_restriction(EMERGENCY), 50);

    printf("=== Speed Limit Unit Tests ===\n\n");

    // Normal range
    check("Normal speed (80 in 90 zone)",check_speed_limit(80, 90), SPEED_NORMAL);

    check("Normal speed (0 in 50 zone)",check_speed_limit(0, 50), SPEED_NORMAL);

    // Warning
    check("At speed limit (90 in 90 zone)",check_speed_limit(90, 90), SPEED_WARNING);

    check("Slightly over limit (95 in 90 zone)",check_speed_limit(95, 90), SPEED_WARNING);

    // Exceeded
    check("Limit exceeded (115 in 90 zone)",check_speed_limit(115, 90), SPEED_LIMIT_EXCEEDED);

    // Critical
    check("Critical speed (145 in 90 zone)",check_speed_limit(145, 90), SPEED_CRITICAL);

    // Sensor fault
    check("Negative speed - sensor fault",check_speed_limit(-1, 90), SPEED_SENSOR_FAULT);

    check("Unrealistic speed - sensor fault",check_speed_limit(301, 90), SPEED_SENSOR_FAULT);

    check("Invalid speed limit - sensor fault",check_speed_limit(80, 0), SPEED_SENSOR_FAULT);

    printf("\n--- Warning Level Tests ---\n\n");

    check("No warning for normal",apply_speed_warning(SPEED_NORMAL), 0);

    check("Soft warning level 1",apply_speed_warning(SPEED_WARNING), 1);

    check("Visual warning level 2",apply_speed_warning(SPEED_LIMIT_EXCEEDED), 2);

    check("Urgent warning level 3",apply_speed_warning(SPEED_CRITICAL), 3);

     printf("=== Fuel Level Unit Tests ===\n\n");

    // Normal range
    check("Full tank (100%)",check_fuel_level(100), FUEL_NORMAL);

    check("Normal level (60%)",check_fuel_level(60), FUEL_NORMAL);

    check("Low warning boundary (25%)",check_fuel_level(25), FUEL_LOW);

    check("Low fuel (20%)",check_fuel_level(20), FUEL_LOW);

    // Critical
    check("Critical boundary (10%)",check_fuel_level(10), FUEL_CRITICAL);

    check("Critical level (5%)",check_fuel_level(5), FUEL_CRITICAL);

    // Empty
    check("Empty tank (0%)",check_fuel_level(0), FUEL_EMPTY);

    // Sensor fault
    check("Negative value - sensor fault",check_fuel_level(-1), FUEL_SENSOR_FAULT);

    check("Over 100 - sensor fault",check_fuel_level(101), FUEL_SENSOR_FAULT);

    printf("\n--- Estimated Range Tests ---\n\n");

    check("Full tank 8L/100km range",get_estimated_range(100, 8), 1000);

    check("Half tank 10L/100km range",get_estimated_range(50, 10), 400);

    check("Invalid consumption",get_estimated_range(50, 0), -1);

    check("Invalid fuel percentage",get_estimated_range(-1, 8), -1);

    


    printf("\n=== Result: %d PASS, %d FAIL ===\n", passed, failed);
    return failed;
}